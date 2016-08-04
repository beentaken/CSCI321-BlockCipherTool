/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

/**
 *
 * @author Aloe2020
 */
public class BlockCipherTool extends Application {
    
    @Override
    public void start(Stage stage) throws Exception {
        BorderPane root = new BorderPane();
        
        Scene scene = new Scene(root, 1374, 828);
        scene.getStylesheets().add(getClass().getResource("/resources/application.css").toExternalForm());
        
        stage.setTitle("CryptoScyph");
        stage.setScene(scene);
        stage.show();
        
        root.setCenter(new MainLayout());
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
