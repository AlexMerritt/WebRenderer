// Coppied from js dir 2
function GetCanvasSize(){
    var canvas = document.getElementById('display');

    return [canvas.width, canvas.height];
}

function SetCanvasSize(iWidth, iHeight){
    var canvas = document.getElementById('display');
    canvas.width = iWidth;
    canvas.height = iHeight;
}

function StartApp() {
    iWidth = window.innerWidth;
    iHeight = window.innerHeight;
    SetCanvasSize(iWidth, iHeight);
    
    canvasSize = GetCanvasSize();

    Module.ccall("Initialize", "null", ["number", "number"], [canvasSize[0], canvasSize[1]]);
    Frame();
}

function Frame(){
    Module.ccall("Update", "null", "null", "null");
    //requestAnimationFrame(Frame);
}

function RunApp(){
    Frame();
}

function Resize() {
    iWidth = window.innerWidth;
    iHeight = window.innerHeight;
    SetCanvasSize(iWidth, iHeight);



    Module.ccall("Resize", "null", ['number', 'number'], [iWidth , iHeight]);
}