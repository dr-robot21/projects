
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.*;

public class Game extends JPanel{


    private final int BOARD_WIDTH,BOARD_HEIGHT;
    // private final int  FPS = 10;

    GameBoard gameBoard;
    
    Player
    player1 = new Player("zakaria", "x"),
    player2 = new Player("anas", "o");

    private  String turn = player1.symbole;

    Mouse mouse;
    // Timer timer;

    public Game(int width,int height,Point frameLoaction) {

        BOARD_WIDTH = width;
        BOARD_HEIGHT = height;

        mouse = new Mouse();
        gameBoard = new GameBoard(BOARD_WIDTH,BOARD_HEIGHT);


        // addMouseMotionListener(new MouseAdapter() {
        //     @Override
        //     public void mouseMoved(MouseEvent e) {
        //         super.mouseMoved(e);
        //         mouse.x = e.getX();
        //         mouse.y = e.getY();

        //         Point mouseOnScreen = e.getLocationOnScreen();
        //         mouse.onScreen = (mouseOnScreen.x >= frameLoaction.x && mouseOnScreen.x <= (frameLoaction.x + BOARD_WIDTH) &&mouseOnScreen.y >= frameLoaction.y && mouseOnScreen.y <= (frameLoaction.y + BOARD_HEIGHT));
        //         repaint();
        //     }
            
        // });
        
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                mouse.setPosition(e.getX(), e.getY());
                updateGameStatus();
                repaint();
            }
            
        });
        
        // timer = new Timer(FPS, new ActionListener() {
        //     @Override
        //     public void actionPerformed(ActionEvent e) {
        //         repaint();
        //     }
        // });

        // timer.start();
    }


    @Override
    protected void paintComponent(Graphics g) {

        Graphics2D g2d = (Graphics2D) g;
        super.paintComponent(g);
        gameBoard.draw(g2d);
    }

    public void updateGameStatus() {

        if(gameBoard.isFull() || player1.win() || player2.win()) {
            player1.replay();
            player2.replay();
            gameBoard.initialize();
            repaint();
            return;
        }


        if(turn.equals(player1.symbole)) {
            player1.play(gameBoard, mouse);
            turn = player2.symbole;
        }else if(turn.equals(player2.symbole)) {
            player2.play(gameBoard, mouse);
            turn = player1.symbole;
        }


        
        if(player1.win()) {
            player1.score++;
            gameBoard.allowToUpdate(false);
            gameBoard.setWinigDetials(player1.winField, player1.winPositon);
        }
        
        if(player2.win()){
            player2.score++;
            gameBoard.allowToUpdate(false);
            gameBoard.setWinigDetials(player2.winField, player2.winPositon);
        }
    }


}
