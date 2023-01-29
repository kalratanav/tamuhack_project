import './App.css';
import React, { useState } from 'react';
import MyVideo from "./video.mp4";
//import { SessionService } from './api/services/SessionService';
// FIXME

function App() {

  const [file1, setFile1] = useState(null);
  const [file2, setFile2] = useState(null);
  const [isShowLogin, setIsShowLogin] = useState(false);
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [token, setToken] = useState("");


  const sendUserData = async (e) => {
    let res = await fetch( `/api/login`, {
      method: "POST",
      headers: {
        "Content-Type": "application/x-www-form-urlencoded"
      },
      body: `username=${username}&password=${password}`
    } ).then( res => res.json() );
    setToken( res["access_token"] );
  }

  const handleClickScroll= () => {
    const element = document.getElementById('section2');
    if (element) {
      element.scrollIntoView({behavior: "smooth"});
    }
  };

  const handleLoginClick = () => {
    setIsShowLogin((isShowLogin) => !isShowLogin)
  }

  const handleClick = () => {
    handleLoginClick()
  }

  const handleSubmission = async (e) => {
      
      try {
        let data = new FormData()
        data.append( "file", file1 )
        let res = await fetch( `/api/teams/upload`, {
          method: "POST",
          headers: {
            "Authorization": `Bearer ${token}`
          },
          body: data
        } ).then( res => res.json() );
        console.log( res )
        console.log("The name of the files are " + file1.name + " " + file2.name);
        console.log("This will now POST the selected files");
        // FIXME
        // SessionService.login({"username":"admin", "password":"password"})
        // .then();
      }
      catch (Exception) {
        console.log("It didn't work");
        console.log(Exception.toString());
      }
  }

  return (
    <div className="App">
      <header className="App-header">
        <div id="section1">
          <div className='topLine'>
            <div className='titleContainer'>
              <h1 className='title'>
                <span>
                  <a className = 'titleLink' href="index.html">Space-Probe</a>
                  </span>
              </h1>
            </div>
            <div className="navbar">
              <nav>
                <ul>
                  <li className="aboutLink" href="#section2" onClick={handleClickScroll}>
                    About
                  </li>
                  <li className='loginLink' onClick={handleClick}> 
                    Login
                  </li>
                </ul>
              </nav>
            </div>
          </div>
          <div className="visualLine">
            <div className='captionContainer'>
              <h2 className='caption'>
                The Modern Office Space Optimizer.
              </h2>
            </div>
            <div className='videoContainer'> 
              <video autoPlay loop muted id="video">
                <source src={MyVideo} type='video/mp4' />
              </video>
            </div>
          </div>
          <div className="LoginLine">
            <div className={`${!isShowLogin ? "active" : ""} show`}>
              <div className="login-form">
                  <div className="form-box solid">
                      <form>
                          <h1 className="login-text">Sign in</h1>
                          <label>UserName</label><br></br>
                          <input 
                              type="text"
                              name="username"
                              className="login-box"
                              id="user"
                              onChange={(e) => setUsername(e.target.value)}
                          /><br></br>
                          <label>Password</label><br></br>
                          <input
                              type="password"
                              name="password"
                              className="login-bo"
                              id="pass"
                              onChange={(e) => setPassword(e.target.value)}
                          /><br></br>
                          <input 
                            type="button" 
                            value="LOGIN" 
                            className="login-btn" 
                            onClick={ sendUserData }
                          />
                      </form>
                  </div>
              </div>
          </div>
          </div>
          <div className='inputContainer'>
            <h2 className='inputCaption'>Upload Files Here:</h2>
            <div className='box'>
            <div className='Form'>
              <label className='PromptLabel'>
                Upload teams.csv and floors.csv files:
              </label>
              <div>
                <input 
                  id="file-upload"
                  type="file"
                  name="file-teams"
                  accept=".csv"
                  onChange={(e) => setFile1(e.target.files[0])}
                />
              </div>
              <div>
                <input 
                  id="file-upload2"
                  type="file"
                  name="file-floors"
                  onChange={(e) => setFile2(e.target.files[0])}
                />
                <div>
                  <button className='button2' onClick={handleSubmission}>Submit</button>
                </div>
              </div>
            </div>
            </div>
          </div>
        </div>
        <div className='infoContainer' id='section2'>
          <h2>
            About Space-Probe
          </h2>
          <p className='info'>
            Space-Probe is an API that helps managers organize their teams into their most optimal positions along the floors. <br></br>
          </p>
          <p className='info'>
          A common challenge that clients have is to help fill up an office space, with varying preferences and team sizes.
          Space-Probe helps clients take their aggregate data about their teams and gives them the most optimal alignment,
          making companies more efficient and cohesive.
          </p>
        </div>
        <p className='names'>Built by Tanav Kalra, Jeremy Eastham, Ren Mai, and David Zhao</p>
      </header>
    </div>
  );
}


export default App;
