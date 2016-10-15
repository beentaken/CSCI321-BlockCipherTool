/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import java.util.UUID;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Modality;
import javafx.stage.Stage;

/**
 *
 * @author Alex
 */
public class SboxNode extends DragNode{
    
    private SboxOptions options = null;
    
    public SboxNode() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/SboxNode.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        
        //setId(UUID.randomUUID().toString());
        options = new SboxOptions();
    }
    
    public SboxOptions getOptions() {
	return this.options;
    }
    
    public void options() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/resources/sboxOptions.fxml"));
        fxmlLoader.setController(options);
        Parent root = fxmlLoader.load();
        options.loadData( this.getInConnections(), this.getOutConnections());
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setOpacity(1);
        stage.setTitle("Options");
        stage.setScene(new Scene(root, 600, 400));
        stage.showAndWait();
    }
}
