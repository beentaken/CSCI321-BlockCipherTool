/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import blockciphertool.wrappers.CipherWrapper;
import blockciphertool.wrappers.PropertiesWrapper;
import blockciphertool.wrappers.SaveLoadTool;
import java.io.File;
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
 * @author Alex, Nick
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
    
    String encryptionMode;
    String encryptionFilename;
    String cipherKey;
    String blocksize;
    String chainMode;
    /**
    * @author Alex
    */     
    public RunConfirm(){
        
    }
    
    /**
    * @author Alex
    */     
    public RunConfirm(String BlockSize, String ChainMode){
	this.blocksize = BlockSize;
	this.chainMode = ChainMode;
    }
    
    
    /**
    * @author Alex
    */    
    @FXML
    private void cancelButtonAction() {
        Stage stage = (Stage) cancel.getScene().getWindow();
        
        stage.close();
    }

    /**
    * @author Nick, Alex
    */	    
    @FXML
    private void runButtonAction() {

	File directory = new File("./../CodeBlocksBackEnd/bin/debug/");
	ProcessBuilder launcher;
	try {
	
	    encryptionFilename = input.getText();
	    cipherKey = key.getText();
	    //encryptionMode = 
	    launcher = new ProcessBuilder( "cipher.exe", encryptionMode, blocksize, encryptionFilename, chainMode, cipherKey  );
	    launcher.directory(directory);
	    
	    try {
		System.out.println(launcher.directory().getCanonicalPath());
		launcher.start();
	    } catch (Exception e) {
		//do nothing
		e.printStackTrace();
	    } finally {
		
	    }
	    
	} catch (Exception e) {
	    
	}

    }
    

}
