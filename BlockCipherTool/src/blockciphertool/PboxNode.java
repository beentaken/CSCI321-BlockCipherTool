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
public class PboxNode extends DragNode{
    
    public PboxNode() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/PboxNode.fxml")
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
    
}
