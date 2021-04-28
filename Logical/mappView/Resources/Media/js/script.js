var c = document.getElementById("myCanvas");
var ctx = c.getContext("2d");
var Foodx = {}
var arr = [];
var val = [];

arr.push({nodeId: "::Program:gHTML_Link.Food.xLoc", attributeId: 13});
arr.push({nodeId: "::Program:gHTML_Link.Food.yLoc", attributeId: 13});

READ();
	  
function READ()
{
  parent.brease.services.opcua.read(arr).done(
  function(value)
  {
	console.log("::Program:gHTML_Link.Food.xLoc: " + value.results["0"].value);
	console.log("::Program:gHTML_Link.Food.yLoc: " + value.results["1"].value);
	ctx.clearRect(0, 0, c.width, c.height);
	ctx.beginPath();
	ctx.moveTo(value.results["0"].value - 1, c.height - value.results["1"].value - 1);
	ctx.lineTo(value.results["0"].value, c.height - value.results["1"].value);
	ctx.stroke();
	READ();
  }, function(){});
}