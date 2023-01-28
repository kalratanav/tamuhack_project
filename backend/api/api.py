from os import system
from threading import Thread
from time import sleep

import uvicorn
from fastapi import FastAPI

app = FastAPI()

@app.get("/ping")
async def ping():
    return "Pong!"

def run_backend():
    uvicorn.run(
        "backend:api",
        host = "0.0.0.0",
        port = 8080,
        log_level = "info",
    )

def run_frontend():
    system( "cd frontend && npm start" )

def generate_client():
    sleep( 1 )
    system( "cd frontend && npm run update-api-client" )

def start_server():
    Thread( target = run_frontend, daemon = True ).start()
    Thread( target = run_backend ).start() # main thread

if __name__ == "__main__":
    start_server()