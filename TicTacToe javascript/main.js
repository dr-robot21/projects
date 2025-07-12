// import { Grid } from "./Grid.js";

import { Board } from "./Board.js";

const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const w = window.innerWidth;
const H = window.innerHeight;
const FPS = 1000/60;

canvas.width = w;
canvas.height = H;


const board = new Board(w/2 - 200,100);
let mouse = {x:0,y:0}

function gameloop() {
    ctx.clearRect(0,0,w,H);
    ctx.fillStyle = "#37344e";
    ctx.fillRect(0,0,w,H);
    board.draw(ctx,mouse);
}


setInterval(gameloop,FPS)
document.addEventListener("mousemove",(e)=>{
    mouse.x = e.clientX;
    mouse.y = e.clientY;
})

document.addEventListener("click",(e)=>{
    let mouseClick = {x:e.clientX,y:e.clientY}
    let position = board.filterMouse(mouseClick);
    board.placeSymbol(position);
})




