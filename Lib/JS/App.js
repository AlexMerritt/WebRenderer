// Coppied from js dir 2
function StartApp() {
    Module.ccall("Initialize", "null", "null", "null");
}

function Frame(){
    Module.ccall("Update", "null", "null", "null");
    //requestAnimationFrame(Frame);
}

function RunApp(){
    Frame();
}

function Resize() {
    iWidth = 640;
    iHeight = 480;
    var canvas = document.getElementById('display');
    canvas.width = iWidth;
    canvas.height = iHeight;

    Module.ccall("Resize", "null", ['number', 'number'], [iWidth , iHeight]);
}