import './App.css';
import React, { useState } from 'react';


function App() {

  const [selectedFile, setSelectedFile] = useState("");
  const [isFilePicked, setIsFilePicked] = useState(false);

  const changeHandler = (event) => {
    setSelectedFile(event.target.files[0]);
    setIsFilePicked(true);
  };


  const handleSubmission = () => {
    const formData = new FormData();

    formData.append('File', selectedFile)

    
  };

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
              <label for="file-upload" class="custom-file-upload">
                <i class="fa fa-cloud-upload"></i> Upload File
              </label>
              <input 
                id="file-upload"
                type="file"
                name="file"
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
            <label for="file-upload2" class="custom-file-upload">
                <i class="fa fa-cloud-upload"></i> Upload File
              </label>
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
