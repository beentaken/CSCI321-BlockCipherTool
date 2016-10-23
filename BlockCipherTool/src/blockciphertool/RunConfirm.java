/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import blockciphertool.wrappers.CipherWrapper;
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
    
     private SaveLoadTool save = null;
    
     
    /**
    * @author Alex
    */     
    public RunConfirm(){
        
    }
    
    /**
    * @author Alex
    */     
    public RunConfirm(SaveLoadTool Save){
        this.save = Save;
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
		//Process should be  "full path to cipher.exe", "get mode from toggle buttons", "blocksize from properties" ,
		    //"filename of file to encrypt", "chain from props", "padding from props", "key to use in plaintext"
	    launcher = new ProcessBuilder( directory.getCanonicalPath() + "/Cipher.exe", directory.getCanonicalPath() + "/save.xml");
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
