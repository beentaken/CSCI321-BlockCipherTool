/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.TableView;
import javafx.scene.layout.AnchorPane;
import javafx.stage.FileChooser;

/**
 *
 * @author csit321lm01a
 */
public class PboxOptions extends AnchorPane{
    
    @FXML TableView myLookupView;
    private final ObservableList<Lookup> data = FXCollections.observableArrayList();
    
    public void PboxOptions() {
        
        System.out.println("blockciphertool.PboxOptions.PboxOptions()");
    }
    
    @FXML
    private void chooseFileButtonAction() {
	FileChooser fileChooser = new FileChooser();
	fileChooser.setTitle("Open Resource File");
	//fileChooser.showOpenDialog();
	System.out.println("loading");
    }
    
    public static class Lookup {
        private final String col1;
        private final String col2;
        private final String col3;
        private final String col4;
        private final String col5;
        private final String col6;
        private final String col7;
        private final String col8;
        
        private Lookup(String newCol1, String newCol2, String newCol3, String newCol4, String newCol5, String newCol6, String newCol7, String newCol8) {
            this.col1 = newCol1;
            this.col2 = newCol2;
            this.col3 = newCol3;
            this.col4 = newCol4;
            this.col5 = newCol5;
            this.col6 = newCol6;
            this.col7 = newCol7;
            this.col8 = newCol8;
        }
        
    }
}
