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
from pydantic import BaseModel, Field

crypt_ctx = CryptContext( schemes = [ "bcrypt" ], deprecated = "auto" )

app = FastAPI()
oauth2_scheme = OAuth2PasswordBearer( tokenUrl = "/api/login" )

class Team( BaseModel ):
    user_id:  int = 0
    floor_id: int = 0
    strength: int = 0
    preferred: list[int] = []
    tolerated: list[int] = []
    no_way:    list[int] = []

class Floor( BaseModel ):
    user_id: int = 0
    id:      int = 0
    name:    str = ""
    size:    int = 0
    teams: list[int] = []

class Token( BaseModel ):
    uuid: str = Field( default_factory = lambda: str( generate_uuid() ) )
    granted: datetime = Field( default_factory = datetime.now )

class User( BaseModel ):
    id:        int = 0
    username:  str = ""
    pass_hash: str = ""
    tokens: list[Token] = []
    floors: list[Floor] = []
    teams:  list[Team]  = []

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

@app.get("/dev/users")
def _get_users():
    return db.users

def get_current_user( token: str = Depends( oauth2_scheme ) ):
    now = datetime.now()
    for user in db.users:
        for token in user.tokens:
            if token.uuid == token:
                if ( token.granted - now ) > timedelta( hours = 1 ):
                    user.tokens.remove( token )
                else:
                    return user
    raise HTTPException(
        status_code = status.HTTP_401_UNAUTHORIZED,
        detail = "Please sign in",
        headers = {
            "WWW-Authenticate": "Bearer"
        }
    )

@app.get("/api/username_available")
def username_available( username: str ):
    for user in db.users:
        if user.username.lower() == username.lower():
            return False
    return True

@app.post("/api/register", status_code = status.HTTP_201_CREATED)
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


@app.post("/api/login")
def login( form_data: OAuth2PasswordRequestForm = Depends() ):
    username = form_data.username
    password = form_data.password
    for user in db.users:
        if user.username.lower() == username.lower():
            if crypt_ctx.verify( password, user.pass_hash ): # TODO: Load from environment variable
                token = Token()
                user.tokens.append( token )
                return { "access_token": token, "token_type": "bearer" }
    raise HTTPException(
        status_code = status.HTTP_401_UNAUTHORIZED,
        detail = "Incorrect username or password"
    )

@app.get("/api/ping")
def ping():
    return "Pong!"

@app.get("/api/teams")
def get_teams( user: dict = Depends( get_current_user ) ):
    return "GET Teams"

def run_backend():
    uvicorn.run(
        "backend.api:app",
        host = "0.0.0.0",
        port = 8080,
        log_level = "info",
#         reload = True
    )

def run_frontend():
    system( "cd my-app && npm start" )

def generate_client():
    sleep( 1 )
    system( "cd my-app && npm run update-api-client" )

def run_server():
    load_users()
    Thread( target = run_frontend, daemon = True ).start()
    Thread( target = run_backend ).start() # main thread

if __name__ == "__main__":
    run_server()