import './App.css';
import React, { useState } from 'react';
//import { SessionService } from './api/services/SessionService';
// FIXME

function App() {

  const [file1, setFile1] = useState(null);
  const [file2, setFile2] = useState(null);

  const handleSubmission = (e) => {
      
      try {
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
                <li className="aboutLink">
                  About
                </li>
                <li className='loginLink'> 
                  Login
                </li>
              </ul>
            </nav>
          </div>
        </div>
        <div className='inputContainer'>
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
      </header>
    </div>
  );
}


export default App;
