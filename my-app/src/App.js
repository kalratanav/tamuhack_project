import './App.css';
import React, { useState } from 'react';


function App() {

  const [selectedFile, setSelectedFile] = useState("");
  const [isFilePicked, setIsFilePicked] = useState("");

  const changeHandler = (event) => {
    setSelectedFile(event.target.files[0]);
    setIsFilePicked(true);
  };

  const handleSubmission = () => {

  };

  return (
    <div className="App">
      <header className="App-header">
        <div className='titleContainer'>
          <h1 className='title'>Team Allottment API</h1>
        </div>
        <div className='inputContainer'>
          <div className='box'>
          <div className='Form'>
            <label className='PromptLabel'>
              Please upload teams.csv file: 
            </label>
            <div>
              <input 
                type="file"
                name="file"
                onChange={changeHandler}
              />
              <div>
                <button className='button' onClick={handleSubmission}>Submit</button>
              </div>
            </div>
            <label className='PromptLabel'>
              Please upload floors.csv file: 
            </label>
            <div>
              <input 
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
