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
public class XorNode extends DragNode{
    
    private String xorSize;
    private XorOptions options = null;
    
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
        options = new XorOptions();
    }
    
    public String getSize() {
        return xorSize;
    }
    
    public void setSize(String newSize) {
        xorSize = newSize;
    }
    
    public void options() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/resources/xorOptions.fxml"));
        fxmlLoader.setController(options);
        Parent root = fxmlLoader.load();
        options.loadData( this.getInConnections(), this.getOutConnections());
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        stage.setOpacity(1);
        stage.setTitle("Options");
        stage.setScene(new Scene(root, 600, 300));
        stage.showAndWait();
    }
    
    public void setOptions(XorOptions xOptions) {
        this.options = xOptions;
    }

    public XorOptions getOptions() {
	return this.options;
    }
}
