import './App.css';
import React, { useState } from 'react';


function App() {

  const [floors, setFloors] = useState("");
  const [teams, setTeams] = useState("");
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
        <div className='Form'>
          <form>
            <label>Enter number of floors: &emsp;
              <input 
                type="text"
                value = {floors}
                onChange={(e) => setFloors(e.target.value)}
              />
            </label>
          </form>
          <form>
            <label>Enter number of teams: &emsp;
              <input 
                type="text" 
                value = {teams}
                onChange={(e) => setTeams(e.target.value)}
              />
            </label>
          </form>
          <label>
            Please upload teams .csv file: 
          </label>
          <div>
            <input 
              type="file"
              name="file"
              onChange={changeHandler}
            />
            <div>
              <button onClick={handleSubmission}>Submit</button>
            </div>
          </div>
        </div>
      </header>
    </div>
  );
}


export default App;
