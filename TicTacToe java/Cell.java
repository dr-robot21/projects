
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;

public class Cell {

    final private int x,y,size;
    final private String CELL_COLOR = "#FFFF00"; 

    private String value = "";


    public Cell(int x,int y,int size) {
        this.x = x * size;
        this.y = y * size;
        this.size = size;
    }

    public void draw(Graphics g) {
        g.setColor(Color.WHITE);
        g.drawRect(x, y, size, size);
        g.setFont(new Font("Arial",Font.BOLD,size));
        g.setColor(Color.decode(CELL_COLOR));

        int valueX = x + size/4;
        int valueY = y + size*3/4;
        g.drawString(value, valueX, valueY);
    }

    public void setValue(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public boolean isEmpty() {
        return "".equals(value);
    }
}
