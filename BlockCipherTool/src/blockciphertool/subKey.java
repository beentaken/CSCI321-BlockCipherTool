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
public class subKey extends DragNode{
    
    private MainLayout main_parent = null;
    
    public subKey() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/subKey.fxml")
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
    
    public void setId(int newId) {
        String keyString = "k" + String.valueOf(newId);
        setId(keyString);
        main_parent.updateKeyIdCounter();
    }
    
    public void setParentMain() {
        main_parent = getParentMain();
    }
    
}
