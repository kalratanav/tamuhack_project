import json
from datetime import datetime, timedelta
from os import system
from threading import Thread
from time import sleep

import pydantic
import uvicorn
from fastapi import FastAPI, Depends, HTTPException
from fastapi.security import OAuth2PasswordBearer, OAuth2PasswordRequestForm
from uuid import uuid4 as generate_uuid

from passlib.context import CryptContext
from starlette import status
from pydantic import BaseModel, Field, SecretStr

crypt_ctx = CryptContext( schemes = ["bcrypt"], deprecated = "auto" )

app = FastAPI( title = "Team Allotment API", generate_unique_id_function = lambda route: route.name )
oauth2_scheme = OAuth2PasswordBearer( tokenUrl = "/api/login" )

class Team( BaseModel ):
    user_id: int = 0
    floor_id: int = 0
    strength: int = 0
    preferred: list[int] = []
    tolerated: list[int] = []
    no_way: list[int] = []

class Floor( BaseModel ):
    user_id: int = 0
    id: int = 0
    name: str = ""
    size: int = 0
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

db: Database = Database()

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

@app.get( "/api/floors", tags = [ "floor" ] )
def get_floors( user: User = Depends( get_current_user ) ):
    return user.floors

def run_backend():
    uvicorn.run(
            app,  # "backend.api:app"
            host = "0.0.0.0",
            port = 8080,
            log_level = "info",
            #         reload = True
    )

def run_frontend():
    system( "cd my-app && npm start" )

def generate_client():
    sleep( 1 )  # wait for uvicorn to start
    system( "cd my-app && npm run update-api-client" )
    Thread( target = run_frontend, daemon = True ).start()

def run_server():
    load_users()
    Thread( target = generate_client, daemon = True ).start()
    Thread( target = run_backend ).start()  # main thread

if __name__ == "__main__":
    run_backend()
