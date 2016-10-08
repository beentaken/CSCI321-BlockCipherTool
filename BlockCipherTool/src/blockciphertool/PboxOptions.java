/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.*;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javax.swing.ProgressMonitorInputStream;

/**
 *
 * @author csit321lm01a
 */
public class PboxOptions extends AnchorPane{
    
    @FXML private TextArea LookupText;
    @FXML private TableView inputTableSizes;
    @FXML private TableView outputTableSizes;
    @FXML private TableColumn InputIds;
    @FXML private TableColumn OutputIds;
    @FXML private TableColumn InputIdSizes;
    @FXML private TableColumn OutputIdSizes;
    
    private final ObservableList<link_list> inputTable = FXCollections.observableArrayList();
    
    public PboxOptions() {
                
        System.out.println("blockciphertool.PboxOptions.PboxOptions()");
    }
    
    public void loadports(int numPort) {
        
        for (int i = 0; i < numPort; i++) {
            inputTable.add(new link_list(i+1, "0"));
        }
        
        InputIds.setCellValueFactory(new PropertyValueFactory<>("linknum"));
        InputIdSizes.setCellValueFactory(new PropertyValueFactory<>("size"));
        
        inputTableSizes.setItems(inputTable);
    }
    
    @FXML
    private void LoadLookupFromFile() {
        Stage stage = new Stage();
	FileChooser fileChooser = new FileChooser();
	fileChooser.setTitle("Open Resource File");
        fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("TXT", "*.txt"));
	File file = fileChooser.showOpenDialog(stage);
	System.out.println("loading");
        
        if (file != null) {
            LookupText.setText(readFile(file));
        }
    }
    
    public static class link_list {
 
        private SimpleIntegerProperty linknum;
        private SimpleStringProperty size;
 
        private link_list(int templinknum, String tempsize) {
            this.linknum = new SimpleIntegerProperty(templinknum);
            this.size = new SimpleStringProperty(tempsize);
        }
 
        public int getlinknum() {
            return linknum.get();
        }
 
        public void setFirstName(int lnum) {
            linknum.set(lnum);
        }
 
        public String getsize() {
            return size.get();
        }
 
        public void setLastName(String lsize) {
            size.set(lsize);
        }
    }
    
    @FXML
    private void save() {
        
    }
    
    /*readFile Was not written by me, aquired online via http://java-buddy.blogspot.com.au/2012/05/read-text-file-with-javafx-filechooser.html*/
    private String readFile(File file){
        StringBuilder stringBuffer = new StringBuilder();
        BufferedReader bufferedReader = null;
         
        try {
 
            bufferedReader = new BufferedReader(new FileReader(file));
             
            String text;
            while ((text = bufferedReader.readLine()) != null) {
                stringBuffer.append(text);
            }
 
        } catch (FileNotFoundException ex) {
            Logger.getLogger(PboxOptions.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(PboxOptions.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                bufferedReader.close();
            } catch (IOException ex) {
                Logger.getLogger(PboxOptions.class.getName()).log(Level.SEVERE, null, ex);
            }
        } 
         
        return stringBuffer.toString();
    }
}
