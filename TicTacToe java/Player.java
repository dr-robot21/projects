import java.awt.Point;

public class Player {

    public String name;
    public int score = 0;

    private boolean isWinning = false;
    public char winField;
    public int winPositon;

    // symbole represent 'x' or 'o'
    public String symbole;

    public Player(String name,String symbole) {
        this.name = name;
        this.symbole = symbole;
    }

    public void play(GameBoard gameBoard,Mouse mouse) {
        gameBoard.update(mouse,symbole);
        checkWining(gameBoard);
    }

    public void replay() {
        isWinning = false;
    }

    private void checkWining(GameBoard gameBoard) {

        // check the rows and colomns
        for(int i = 0; i < 3; i++) {
            Cell col1,col2,col3;
            Cell row1,row2,row3;

            col1 = gameBoard.getCurrentCell(new Point(i,0));
            col2 = gameBoard.getCurrentCell(new Point(i,1));
            col3 = gameBoard.getCurrentCell(new Point(i,2));

            row1 = gameBoard.getCurrentCell(new Point(0,i));
            row2 = gameBoard.getCurrentCell(new Point(1,i));
            row3 = gameBoard.getCurrentCell(new Point(2,i));

            if(col1.getValue().equals(symbole) && col2.getValue().equals(symbole) && col3.getValue().equals(symbole)) {
                isWinning = true;
                winField = 'C';
                winPositon = i;
            }

            if(row1.getValue().equals(symbole) && row2.getValue().equals(symbole) && row3.getValue().equals(symbole)) {
                isWinning = true;
                winField = 'R';
                winPositon = i;
            }
        }
        
        // check the diagonals
        Cell diag1_1,diag1_2,diag1_3;
        Cell diag2_1,diag2_2,diag2_3;

        diag1_1 = gameBoard.getCurrentCell(new Point(0,0));
        diag1_2 = gameBoard.getCurrentCell(new Point(1,1));
        diag1_3 = gameBoard.getCurrentCell(new Point(2,2));


        diag2_1 = gameBoard.getCurrentCell(new Point(0,2));
        diag2_2 = gameBoard.getCurrentCell(new Point(1,1));
        diag2_3 = gameBoard.getCurrentCell(new Point(2,0));

        if(diag1_1.getValue().equals(symbole) && diag1_2.getValue().equals(symbole) && diag1_3.getValue().equals(symbole)) {
            isWinning = true;
            winField = 'D';
            winPositon = 1;
        }
        
        if(diag2_1.getValue().equals(symbole) && diag2_2.getValue().equals(symbole) && diag2_3.getValue().equals(symbole)) {
            isWinning = true;
            winField = 'D';
            winPositon = 2;
        }
    }
    
    
    public boolean win() {
        return isWinning;
    }
}
