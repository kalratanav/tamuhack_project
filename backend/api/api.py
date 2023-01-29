import csv
import json
import os
from datetime import datetime, timedelta
from os import system
from subprocess import Popen, PIPE
from threading import Thread
from time import sleep

import pydantic
import uvicorn
from fastapi import FastAPI, Depends, HTTPException, UploadFile
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from uuid import uuid4 as generate_uuid

from passlib.context import CryptContext
from starlette import status
from pydantic import BaseModel, Field, SecretStr

import pandas as pd

crypt_ctx = CryptContext( schemes = ["bcrypt"], deprecated = "auto" )

app = FastAPI( title = "Team Allotment API", generate_unique_id_function = lambda route: route.name )
oauth2_scheme = OAuth2PasswordBearer( tokenUrl = "/api/login" )

class Team( BaseModel ):
    id: int = 0
    user_id: int = 0
    floor_id: int = -1
    strength: int = 0
    preferred: list[int] = []
    tolerated: list[int] = []
    no_way: list[int] = []

class Floor( BaseModel ):
    id: int = 0
    user_id: int = 0
    name: str = ""
    occupied: int = 0
    min_capacity: int = 0
    max_capacity: int = 0
    teams: list[int] = []

class Token( BaseModel ):
    uuid: SecretStr = Field( default_factory = lambda: SecretStr( str( generate_uuid() ) ) )
    granted: datetime = Field( default_factory = datetime.now )

class User( BaseModel ):
    id: int = 0
    username: str = ""
    pass_hash: SecretStr = ""
    tokens: list[Token] = []
    floors: list[Floor] = []
    teams: list[Team] = []

class Database( BaseModel ):
    users: list[User] = []

db: Database = Database(
    users = [
        User(
            id = 0,
            username = "admin",
            pass_hash = SecretStr( "$2b$12$Zdh.5LquW4bSMTiwMKC1wuRT1C8xWuTXQFEMdDhLDx0EYHTnmm9xa" ), # "password"
            tokens = [
                Token(
                    uuid = SecretStr( "test" ),
                    granted = datetime.now()
                )
            ]
        )
    ]
)

def load_users():
    global db
    try:
        db = pydantic.parse_file_as( path = "db.json", type_ = Database )
    except IOError:
        db = Database()

def save_users():
    with open( "db.json", "w" ) as f:
        f.write( db.json( indent = 2 ) )

@app.get( "/dev/users", tags = ["dev"] )
def _get_users():
    return db.users

def get_current_user( token: str = Depends( oauth2_scheme ) ):
    now = datetime.now()
    for db_user in db.users:
        for db_token in db_user.tokens:
            if db_token.uuid.get_secret_value() == token:
                if (db_token.granted - now) > timedelta( hours = 1 ):
                    db_user.tokens.remove( db_token )
                else:
                    return db_user
    raise HTTPException(
            status_code = status.HTTP_401_UNAUTHORIZED,
            detail = "Invalid token" if token else "Please sign in",
            headers = {
                "WWW-Authenticate": "Bearer"
            }
    )

@app.get( "/api/username-available", tags = [ "users" ] )
def username_available( username: str ):
    for user in db.users:
        if user.username.lower() == username.lower():
            return False
    return True

@app.post( "/api/register", status_code = status.HTTP_201_CREATED, tags = [ "session" ] )
def register( form_data: OAuth2PasswordRequestForm = Depends() ):
    username = form_data.username
    pass_hash = crypt_ctx.hash( form_data.password )
    for user in db.users:
        if user.username.lower() == username.lower():
            raise HTTPException(
                    status_code = status.HTTP_401_UNAUTHORIZED,
                    detail = "An account already exists with that username"
            )
    db.users.append( User(
            id = len( db.users ),
            username = username,
            pass_hash = pass_hash
    ) )

@app.post( "/api/login", tags = [ "session" ] )
def login( form_data: OAuth2PasswordRequestForm = Depends() ):
    username = form_data.username
    password = form_data.password
    for user in db.users:
        if user.username.lower() == username.lower():
            if crypt_ctx.verify( password, user.pass_hash.get_secret_value() ):  # TODO: Load from environment variable
                token = Token()
                user.tokens.append( token )
                return { "access_token": token.uuid.get_secret_value(), "token_type": "bearer" }
    raise HTTPException(
            status_code = status.HTTP_401_UNAUTHORIZED,
            detail = "Incorrect username or password"
    )

@app.post( "/api/logout", status_code = status.HTTP_200_OK, tags = [ "session" ] )
def logout( token: str = Depends( oauth2_scheme ) ):
    for db_user in db.users:
        for db_token in db_user.tokens:
            if db_token.uuid.get_secret_value() == token:
                db_user.tokens.remove( db_token )

@app.post( "/api/logout-all", status_code = status.HTTP_200_OK, tags = [ "session" ] )
def logout_all( token: str = Depends( oauth2_scheme ) ):
    for db_user in db.users:
        for db_token in db_user.tokens:
            if db_token.uuid.get_secret_value() == token:
                db_user.tokens.clear()
                break

@app.get( "/api/ping" )
def ping():
    return "Pong!"

@app.get( "/api/user", tags = [ "user" ] )
def get_user( user: User = Depends( get_current_user ) ):
    return user

@app.get( "/api/teams", tags = [ "team" ] )
def get_teams( user: User = Depends( get_current_user ) ):
    return user.teams

@app.post( "/api/teams/upload", tags = [ "team" ] )
def upload_teams_csv( teams_csv: UploadFile, user: User = Depends( get_current_user ) ):
    if not teams_csv.filename.endswith( ".csv" ):
        raise HTTPException(
            status_code = status.HTTP_400_BAD_REQUEST,
            detail = f"Incorrect filetype for file {teams_csv.filename}"
        )
    df = pd.read_csv( teams_csv.file )
    teams = []
    for id, row in df.iterrows():
        # Team, Strength, Preferred, Tolerated, No way
        teams.append( Team(
            id        = int( row["Team"] ),
            user_id   = user.id,
            strength  = int( row["Strength"] ),
            preferred = [ int( id ) for id in str( row["Preferred"] ).split( " " ) ],
            tolerated = [ int( id ) for id in str( row["Tolerated"] ).split( " " ) ],
            no_way    = [ int( id ) for id in str( row["No way"]    ).split( " " ) ]
        ) )
    user.teams = teams
    return teams

@app.get( "/api/floors", tags = [ "floor" ] )
def get_floors( user: User = Depends( get_current_user ) ):
    return user.floors

@app.post( "/api/floors/upload", tags = [ "floor" ] )
def upload_floors_csv( floors_csv: UploadFile, user: User = Depends( get_current_user ) ):
    if not floors_csv.filename.endswith( ".csv" ):
        raise HTTPException(
            status_code = status.HTTP_400_BAD_REQUEST,
            detail = f"Incorrect filetype for file {floors_csv.filename}"
        )
    df = pd.read_csv( floors_csv.file )
    floors = []
    for id, row in df.iterrows():
        # Floor, Max Capacity
        floors.append( Floor(
            id = len( floors ),
            name = row["Floor"],
            min_capacity = row["Max Capacity"] // 4 + 1,
            max_capacity = row["Max Capacity"]
        ) )
    floors.append( Floor(
        id = -1,
        name = "N/A",
        max_capacity = 999999999
    ) )
    user.floors = floors
    return floors

@app.post( "/api/calculate", tags = [ "user" ] )
def calculate( user: User = Depends( get_current_user ) ):
    # example_input = "5 43 81 73 54 97 11 22 4 2 4 6 11 3 3 8 10 3 5 7 9 45 3 1 3 5 3 6 7 11 4 4 8 9 10 34 3 1 2 11 1 7 6 4 5 6 8 9 10 51 1 10 2 1 3 7 2 5 6 7 8 9 11 11 4 1 2 3 4 3 9 10 11 3 6 7 8 37 2 7 10 2 1 8 6 2 3 4 5 9 11 42 6 1 2 3 4 5 6 2 10 11 2 8 9 16 2 1 10 3 2 4 11 5 3 5 6 7 9 29 2 1 5 2 2 10 6 3 4 6 7 8 11 56 4 2 6 7 11 3 4 5 8 3 1 3 9 49 3 1 4 5 6 2 3 6 7 9 10 1 8\n"
    cpp_input = ""
    cpp_input += str( len( user.floors ) - 1 ) + " "
    for floor in user.floors:
        if floor.id != -1:
            cpp_input += str( floor.max_capacity ) + " "
    cpp_input += str( len( user.teams ) - 1 ) + " "
    for team in user.teams:
        cpp_input += str( team.strength ) + " "
        cpp_input += str( len( team.preferred ) ) + " "
        cpp_input += " ".join( [ str( i ) for i in team.preferred ] ) + " "
        cpp_input += str( len( team.tolerated ) ) + " "
        cpp_input += " ".join( [ str( i ) for i in team.tolerated ] ) + " "
        cpp_input += str( len( team.no_way ) ) + " "
        cpp_input += " ".join( [ str( i ) for i in team.no_way ] ) + " "
    cpp_input = cpp_input.rstrip( " " ) + "\n"
    p = Popen( [ os.path.join( ".", "backend", "algorithm", "a.out" ) ], stdin = PIPE, stdout = PIPE )
    result = p.communicate( cpp_input.encode( "ascii" ) )[0].decode( "ascii" )
    best_arrangement = [ int( i ) for i in result.strip().split( "\n" )[0].split( " " ) ]
    for floor in user.floors:
        floor.teams.clear()
        floor.occupied = 0
    for floor_assignment, team in zip( best_arrangement, user.teams ):
        team.floor_id = floor_assignment
        for floor in user.floors:
            if floor.id == floor_assignment:
                floor.teams.append( team.id )
                floor.occupied += team.strength
    return user

def run_backend():
    uvicorn.run(
            app,  # "backend.api:app"
            host = "0.0.0.0",
            port = 8080,
            log_level = "info",
            #         reload = True
    )

def run_frontend( generate_client = True ):
    sleep( 1 )  # wait for uvicorn to start
    system( "cd my-app && npm run update-api-client && npm start" )

def run_server():
    # load_users()
    Thread( target = run_frontend, daemon = True ).start()
    run_backend()  # main thread

if __name__ == "__main__":
    run_backend()
