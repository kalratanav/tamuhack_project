import './App.css';
import React, { useState } from 'react';
var FormData = require('form-data');

function App() {

  const [selectedFile, setSelectedFile] = useState("");
  const [isFilePicked, setIsFilePicked] = useState(false);
  const [teamsOrLevels, setTeamsOrLevels] = useState("");

  const changeHandler = (event) => {
    setSelectedFile(event.target.files[0]);
    setIsFilePicked(true);
  };

  const handleSubmission = (e) => {
    if (isFilePicked)
    {
      const files = selectedFile;
      console.log("This will now POST the selectedFile");
      console.log("The name of the file is " + files.name)

    }
  }

  return (
    <div className="App">
      <header className="App-header">
        <div className='titleContainer'>
          <h1 className='title'>
            <span>Team Allottment API</span>
          </h1>
        </div>
        <div className='inputContainer'>
          <div className='box'>
          <div className='Form'>
            <label className='PromptLabel'>
              Upload teams.csv file: 
            </label>
            <div>
              <input 
                id="file-upload"
                type="file"
                name="file"
                accept=".csv"
                onChange={changeHandler}
              />
              <div>
                <button className='button' onClick={handleSubmission}>Submit</button>
              </div>
            </div>
            <label className='PromptLabel'>
              Upload floors.csv file: 
            </label>
            <div>
              <input 
                id="file-upload2"
                type="file"
                name="file"
                onChange={changeHandler}
              />
              <div>
                <button className='button' onClick={handleSubmission}>Submit</button>
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
