/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import java.util.UUID;
import javafx.fxml.FXMLLoader;

/**
 *
 * @author csit321lm01a
 */
public class XorNode extends DragNode{
    
    private String xorSize;
    
    public XorNode() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/XorNode.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        //setId(UUID.randomUUID().toString());
    }
    
    public String getSize() {
        return xorSize;
    }
    
    public void setSize(String newSize) {
        xorSize = newSize;
    }
    
}
