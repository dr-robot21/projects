import { Grid } from "./Grid.js"
export class Board {

    constructor(x,y) {
        this.x = x;
        this.y = y;
        this.grid = new Grid({
            x:this.x,
            y:this.y,
            cols:3,
            rows:3,
            size:150,
            color:"#f89cff"
        });

        this.player1 = {
            symbole:"x",
            score:0
        };
        
        this.player2 = {
            symbole:"o",
            score:0
        };

        this.turn = "x";
        this.board = [[0,0,0],[0,0,0],[0,0,0]]
        this.moves = 0;
        this.isWinner = false;
        this.winner = "";
        this.winningPostion = {
            place:"",
            number:NaN
        }

        this.timer = 0;
        this.isGameOver = false;
    }

    initialize() {
        this.board = [[0,0,0],[0,0,0],[0,0,0]];
        this.moves = 0;
        this.isWinner = false;
        this.winner = "";
        this.winningPostion = {
            place:"",
            number:NaN
        }
    }

    draw(ctx,mouse) {
        let position = this.filterMouse(mouse);
        this.drawGameScore(ctx)
        this.drawHelpRect(ctx,position);
        this.grid.draw(ctx);
        this.drawBoard(ctx);
        this.drawWiningLine(ctx);

        if(this.isGameOver) {
            this.timer++;
        }

        if(this.timer > 120) {
            this.initialize();
            this.timer = 0;
            this.isGameOver = false;
        }
    }

    drawGameScore(ctx) {
        ctx.fillStyle = "white";
        let height = 50;
        let x = this.x - this.grid.lineWidth/2;
        let y = this.y - height;
        let width = this.grid.size*this.grid.cols + this.grid.lineWidth;
        ctx.fillRect(x,y,width,height)
        ctx.font = "20px Arial"
        ctx.fillStyle = "black"
        ctx.fillText("Player 1 : "+this.player1.score,x + 50,y + 30);
        ctx.fillText(this.player2.score + " : Player 2",x + width - 155,y + 30);
        
        let message = "";

        if(this.isWinner) {
            message = "Winner: "+this.winner;
        }else if(!this.isWinner && this.moves === 9) {
            message = "Draw"
        }else {
            message = "Turn: " + this.turn;
        }

        ctx.fillStyle = this.grid.color;
        ctx.font = "20px Arial"
        ctx.fillText(message,this.x + (this.grid.cols*this.grid.size)/2 - 30,y + 30)

    }

    drawBoard(ctx) {
        for(let i = 0; i < 3; i++) {
            for(let j = 0; j < 3; j++) {

                ctx.font = `${this.grid.size}px Arial` ;
                ctx.fillStyle = "#6fddff";
                
                let x = this.grid.size/4 + this.x + i * this.grid.size;
                let y = this.grid.size * 3/4 + this.y + j * this.grid.size;
                
                if(this.board[i][j] === 1) {
                    ctx.fillText(this.player1.symbole,x,y);
                }else if(this.board[i][j] === -1) {
                    ctx.fillText(this.player2.symbole,x,y);
                }
            }
        }
    }

    drawHelpRect(ctx,position) {
        if(isNaN(position.x) || isNaN(position.y)) return;
        let color = this.isPlacebale(position) ? "#6fffdb" : "#ff92b8";
        ctx.fillStyle = color
        let x = this.x + this.grid.size*position.x;
        let y = this.y + this.grid.size*position.y
        ctx.fillRect(x,y,this.grid.size,this.grid.size);
    }
    filterMouse(mouse) {
        let output = {x:NaN,y:NaN};
        if (mouse.x > this.x && mouse.x < this.x + this.grid.size * this.grid.cols && mouse.y > this.y && mouse.y < this.y + this.grid.size * this.grid.rows) {
            output.x = Math.floor((mouse.x - this.x ) / this.grid.size)
            output.y = Math.floor((mouse.y - this.y ) / this.grid.size)
            
        }
        return output;
    }
    placeSymbol(position) {
        if(isNaN(position.x) || isNaN(position.y) || !this.isPlacebale(position) || this.isWinner) return;
        console.log(position);
        if(this.turn == this.player1.symbole) {
            this.board[position.x][position.y] = 1;
            this.turn = this.player2.symbole;
        }else if(this.turn == this.player2.symbole) {
            this.board[position.x][position.y] = -1;
            this.turn = this.player1.symbole;
        }
        this.moves++;
        this.checkWinner();

        if(this.moves ===  9 && !this.isWinner) {
            this.isGameOver = true;
        } 

        if(this.isWinner) {
            this.isGameOver = true;
            if(this.winner == "x" ) {
                this.player1.score++;
            }else {
                this.player2.score++;
            }
        }
        
    }
    isPlacebale(position) {
        return this.board[position.x][position.y] === 0;
    }

    checkWinner() {
        let cols = [
            this.board[0][0] + this.board[0][1] + this.board[0][2],
            this.board[1][0] + this.board[1][1] + this.board[1][2],
            this.board[2][0] + this.board[2][1] + this.board[2][2] 
        ] 
        
        let rows = [
            this.board[0][0] + this.board[1][0] + this.board[2][0],
            this.board[0][1] + this.board[1][1] + this.board[2][1],
            this.board[0][2] + this.board[1][2] + this.board[2][2]
        ]


        let diagonal = [
            this.board[0][0] + this.board[1][1] + this.board[2][2],
            this.board[0][2] + this.board[1][1] + this.board[2][0],
        ]

        for (let i in cols ) {

            let item = cols[i];
            
            if(item === 3) {
                this.isWinner = true;
                this.winner = "x";
            }else if(item == -3) {
                this.isWinner = true;
                this.winner = "0";
            }

            if(this.isWinner) {
                this.winningPostion.place = "cols";
                this.winningPostion.number = i;
                return;
            }
        }
        for (let i in rows ) {

            let item = rows[i];

            if(item === 3) {
                this.isWinner = true;
                this.winner = "x";
            }else if(item == -3) {
                this.isWinner = true;
                this.winner = "0";
            }

            if(this.isWinner) {
                this.winningPostion.place = "rows";
                this.winningPostion.number = i;
                return;
            }
        }
        for (let i in diagonal ) {

            let item = diagonal[i];

            if(item === 3) {
                this.isWinner = true;
                this.winner = "x";
            }else if(item == -3) {
                this.isWinner = true;
                this.winner = "0";
            }

            if(this.isWinner) {
                this.winningPostion.place = "diag";
                this.winningPostion.number = i;
                return;
            }
        }

    }


    drawWiningLine(ctx) {
        if(this.isWinner) {
            let from = {x:NaN,y:NaN}
            let to = {x:NaN,y:NaN}
            
            switch (this.winningPostion.place) {
                case "cols":
                    from.x = this.x + 1/2*this.grid.size + this.winningPostion.number*this.grid.size;
                    from.y = this.y + 1/4*this.grid.size;

                    to.x = from.x
                    to.y = from.y + this.grid.size*this.grid.cols - this.grid.size/2;

                    break;

                case "rows":

                    from.x = this.x + 1/4*this.grid.size;
                    from.y = this.y + 1/2*this.grid.size + this.winningPostion.number*this.grid.size;

                    to.x = from.x + this.grid.size*this.grid.rows - this.grid.size/2;
                    to.y = from.y;

                    break;

                case "diag":
                    if(this.winningPostion.number == 0) {
                        from.x = this.x + this.grid.size/4;
                        from.y = this.y + this.grid.size/4;

                        to.x = this.x + this.grid.cols*this.grid.size - this.grid.size/4;

                        to.y = this.y + this.grid.cols*this.grid.size - this.grid.size/4;
                    }else{
                        from.x = this.x + this.grid.cols*this.grid.size - this.grid.size/4;
                        from.y = this.y + this.grid.size/4;

                        to.x = this.x + this.grid.size/4;
                        to.y = this.y + this.grid.rows*this.grid.size - this.grid.size/4;
                    }

                    break;
            
                default:
                    break;
                }
            
            ctx.beginPath();
            ctx.lineWidth = 10
            ctx.strokeStyle = this.grid.color;
            ctx.moveTo(from.x,from.y);
            ctx.lineTo(to.x,to.y);
            ctx.stroke();
        }
    }
}