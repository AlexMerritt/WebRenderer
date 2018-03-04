// Coppied from js dir 2
function StartApp(){
    Module.ccall("Initialize", "null", "null", "null");
}

function Frame(){
    Module.ccall("Update", "null", "null", "null");
    // requestAnimationFrame(Frame);
}

function RunApp(){
    Frame();
}