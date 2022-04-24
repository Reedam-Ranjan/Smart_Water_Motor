const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card {
  max-width: 400px;
  min-height: 250px;
  background: #02b875;
  padding: 30px;
  box-sizing: border-box;
  color: #FFF;
  margin:20px;
  box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
.button {
  background: blue;
  padding: 10px;
  box-sizing: border-box;
  color: #FFF;
  margin:20px;
}

</style>
<body>

<div class="card">
  <h1>Smart Motor</h1><br>
  <h2>Water Flow Rate:<span id="flowSensorValue">0</span> l/hour</h2><br>
  <button id="relayButton" class="button"><span id="RelayState"></span></button>
  <h1>Tank Level</h1><br>
  <h3>Current Tank Fill Level: <span id="fillPercentage">0</span>%</h3><br>
  <h3>Current Water Level: <span id="tankLevel">0</span> litres</h3><br>
  <h3>Tank Capacity: <span id="tankCapacity">0</span> litres</h3><br>
  <button id="refreshButton" class="button">Refresh</button>
  <h4>Last Refreshed: <span id="lastRefresh"></span></h4>
</div>
<script>


// For todays date;
Date.prototype.today = function () { 
    return ((this.getDate() < 10)?"0":"") + this.getDate() +"/"+(((this.getMonth()+1) < 10)?"0":"") + (this.getMonth()+1) +"/"+ this.getFullYear();
}

// For the time now
Date.prototype.timeNow = function () {
     return ((this.getHours() < 10)?"0":"") + this.getHours() +":"+ ((this.getMinutes() < 10)?"0":"") + this.getMinutes() +":"+ ((this.getSeconds() < 10)?"0":"") + this.getSeconds();
}

setInterval(function() {
  // Call a function repetatively with 1 Second interval
  getFlowSensorData();
  getRelayState();
}, 1000); //1000mSeconds update rate

function getFlowSensorData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("flowSensorValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readFlowSensor", true);
  xhttp.send();
}

function getRelayState() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("RelayState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "getRelayState", true);
  xhttp.send();
}


function getFillPercentage() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("fillPercentage").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "getTankPercentageLevel", true);
  xhttp.send();
}

function getWaterLevel() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("tankLevel").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "getTankWaterLevel", true);
  xhttp.send();
}

document.getElementById("refreshButton").onclick = function handleRelay() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.status == 200) {
      var newDate = new Date();
      document.getElementById("lastRefresh").innerHTML = new Date().timeNow() + " " + new Date().today();
    }
  };
  xhttp.open("GET", "refreshValues", true);
  xhttp.send();
}

document.getElementById("relayButton").onclick = function handleRelay() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("RelayState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "handleRelay", true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";
