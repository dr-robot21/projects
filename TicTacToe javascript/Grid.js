export class Grid {

    constructor (options) {

        this.x = options.x;
        this.y = options.y;
        this.cols = options.cols;
        this.rows = options.rows;
        this.size = options.size;
        this.color = options.color;
        this.lineWidth = 3;
    }

    drawLine(ctx,from,to) {
        ctx.beginPath();
        ctx.moveTo(from.x,from.y);
        ctx.lineTo(to.x,to.y);
        ctx.stroke();     
    }
    
    draw(ctx){
        ctx.strokeStyle = this.color;
        ctx.lineWidth = this.lineWidth;

        for(let i = 0 ; i <= this.rows ; i++) {
            let from = {
                x: this.x - this.lineWidth/2,
                y: this.y+i*this.size
            }
            let to = {
                x: this.x + this.cols*this.size + this.lineWidth/2,
                y: this.y+i*this.size
            }
            this.drawLine(ctx,from,to);
        }
        
        for (let j = 0; j <= this.cols; j++) {
            let from = {
                x: this.x + j*this.size,
                y: this.y
            }
            let to = {
                x: this.x + j*this.size,
                y: this.y + this.rows*this.size
            }            
            this.drawLine(ctx,from,to);
        }

    }

}