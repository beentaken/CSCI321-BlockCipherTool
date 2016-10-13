/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import blockciphertool.wrappers.CipherWrapper;
import blockciphertool.wrappers.SaveLoadTool;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

/**
 *
 * @author csit321lm01a
 */
public class RunConfirm extends AnchorPane{
    
    @FXML RadioButton encrypt;
    @FXML RadioButton decrypt;
    @FXML ToggleGroup mode;
    @FXML TextField key;
    @FXML TextArea input;
    @FXML TextArea output;
    @FXML Button run;
    @FXML Button cancel;
    
     private SaveLoadTool save = null;
     private CipherWrapper cWrapper = null;
    
    public RunConfirm(){
        
    }
    
    public RunConfirm(CipherWrapper newCipherWrapper) {
        cWrapper = newCipherWrapper;
    }
    
    @FXML
    private void cancelButtonAction() {
        Stage stage = (Stage) cancel.getScene().getWindow();
        
        stage.close();
    }

	    
    @FXML
    private void runButtonAction() {
	
	//CipherWrapper cipher = CipherWrapper.generateCipherWrapper();
	
	
	SaveLoadTool saveController = new SaveLoadTool();
	saveController.saveAsXml("save.xml");
        
        
    }
    

}
