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
 * @author Alex
 */
public class Key extends DragNode{
    
    public Key() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/Key.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        //setId(UUID.randomUUID().toString());
        setId("-1");
    }
}
