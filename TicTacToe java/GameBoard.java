import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Point;
import java.util.ArrayList;


public class GameBoard {

    private ArrayList<ArrayList<Cell>> gameBoard;
    private final int boardWidth;
    private final int boardHeight;


    final private int COLS = 3,ROWS = 3,CELL_SIZE = 200;
    private int totalMoves = 0;

    private boolean allowedToUpdate = true;
    

    // win situation
    private boolean allowdToDrawWinigLine = false;
    private char winingField;
    private int winingPos;

    public GameBoard(int width,int height) {
        this.boardWidth = width;
        this.boardHeight = height;
        initialize();
    }

    public final void initialize() {
        gameBoard = new ArrayList<>(ROWS);
        for(int i = 0 ; i < ROWS ; i++) {
            ArrayList<Cell> row = new ArrayList<>(COLS);
            for(int j = 0; j < COLS ; j++) {
                Cell cell = new Cell(j, i, CELL_SIZE);
                row.add(cell);
            }
            gameBoard.add(row);
        }

        totalMoves = 0;
        allowedToUpdate = true;
        allowdToDrawWinigLine = false;
    }

    public void draw(Graphics2D g) {
        for(ArrayList<Cell> row : gameBoard) {
            for(Cell cell : row) {
                cell.draw(g);
            }
        } 

        if(allowdToDrawWinigLine) {
            drawWiningLine(g, winingField, winingPos);
        }
    }

    public void update(Mouse mouse,String symbole) {

        if(!allowedToUpdate) return;
        Point cellPosition = getCurrentCellPosition(mouse);
        Cell currentCell = getCurrentCell(cellPosition);

    
        if(currentCell.isEmpty()) {
            currentCell.setValue(symbole);
            totalMoves++;
        }

    }

    public void allowToUpdate(boolean isAllowd) {
        allowedToUpdate = isAllowd;
    }

    public void setWinigDetials(char field,int pos) {
        allowdToDrawWinigLine = true;
        winingField = field;
        winingPos = pos;
    }


    public Point getCurrentCellPosition(Mouse mouse) {
        Point p = new Point();
        p.x = (int)(mouse.x / CELL_SIZE);
        p.y = (int)(mouse.y / CELL_SIZE);
        return p;
    }

    public Cell getCurrentCell(Point position) { 
        return gameBoard.get(position.y).get(position.x);
    }


    public boolean isFull() {
        return totalMoves >= 9;
    }
    
    
    
    public void drawWiningLine(Graphics2D g2d,char field,int pos) {
      Point start = new Point(0,0),
      end = new Point(0,0);

      int margin1 = CELL_SIZE/6;
      int margin2 = CELL_SIZE/2;

        switch (field) {    
          case 'C' -> {
              start.x = CELL_SIZE*pos + margin2;
              start.y = margin1;
              end.x = start.x;
              end.y = boardHeight - margin1;
          }
          case 'R' -> {
              start.x = margin1;
              start.y = CELL_SIZE * pos + margin2;
              end.x = boardWidth - margin1;
              end.y = start.y;
          }
          case 'D' -> { 
              if(pos == 1) {
                  start.x = margin1;
                  start.y = margin1;

                  end.x = boardWidth - margin1;
                  end.y = boardHeight - margin1;
              }else if(pos == 2) {
                  start.x = boardWidth - margin1;
                  start.y = margin1;

                  end.x = margin1;
                  end.y = boardHeight - margin1;
              }
          }
        }

        g2d.setStroke(new BasicStroke(10));
        g2d.setColor(Color.GREEN);
        g2d.drawLine(start.x, start.y, end.x, end.y);
    } 
}
 