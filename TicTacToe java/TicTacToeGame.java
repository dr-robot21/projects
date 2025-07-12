
import java.awt.*;
import javax.swing.*;

public class TicTacToeGame {

    final static private int SCREEN_WIDTH = 600,
    SCREEN_HEIGHT = 600;


    public static void main(String[] args) {
        JFrame window = new JFrame();
        window.setTitle("Tic Tac Toe");
        window.setSize(SCREEN_WIDTH,SCREEN_HEIGHT);
        window.setLocationRelativeTo(null);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setResizable(false);

        Dimension preferredSize = new Dimension(SCREEN_WIDTH,SCREEN_HEIGHT);
        window.setVisible(true);
        
        Point frameLoaction = window.getLocationOnScreen();
        Game game = new Game(SCREEN_WIDTH,SCREEN_HEIGHT,frameLoaction);

        game.setPreferredSize(preferredSize);
        game.setBackground(Color.BLACK);
        window.add(game);
        window.pack();
        
    }
}