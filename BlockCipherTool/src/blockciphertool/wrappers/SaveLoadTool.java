/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import blockciphertool.NodeLink;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.Marshaller;
import blockciphertool.PboxNode;
import blockciphertool.SboxNode;
import blockciphertool.XorNode;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javax.xml.bind.Unmarshaller;
/**
 *
 * @author Nick
 * @class save tool to generate or load xml
 */
public class SaveLoadTool {
    private SaveWrapper saveWrapper = new SaveWrapper();
    
    public void AddProperties(String wrapperType) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    temp.AddProperties("2", "64", "16", "counter", "zero padding", "1", "2");
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddProperties("2", "64", "16", "counter", "zero padding", "1", "2");
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    
	}
    }
    public void AddProperties(String wrapperType, String NumRounds, String BlockSize, String KeySize, String ChainMode, String Padding, String StartId, String EndId ) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    temp.AddProperties(NumRounds, BlockSize, KeySize, ChainMode, Padding, StartId, EndId);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddProperties(NumRounds, BlockSize, KeySize, ChainMode, Padding, StartId, EndId);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    
	}
    }
    
    public void AddPBoxs(String wrapperType, List<PboxNode> pboxs) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    temp.AddPBoxs(pboxs);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddPBoxs(pboxs);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddPBoxs(pboxs);
	    saveWrapper.setDecryptionCipher(temp);
	}
    }
    
    public void AddSBoxes(String wrapperType, List<SboxNode> sboxs) {	
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    temp.AddSBoxes(sboxs);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddSBoxes(sboxs);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddSBoxes(sboxs);
	    saveWrapper.setDecryptionCipher(temp);
	}
    }
    
    public void AddXors(String wrapperType, List<XorNode> xors) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    temp.AddXors(xors);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddXors(xors);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddXors(xors);
	    saveWrapper.setDecryptionCipher(temp);
	}
    }
    
    public void AddConnections(String wrapperType, List<NodeLink> connections) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    temp.AddConnections(connections);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddConnections(connections);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    temp.AddConnections(connections);
	    saveWrapper.setDecryptionCipher(temp);
	}
    }

    
    public void loadAsXml(String filename) {
	try {
	    JAXBContext context = JAXBContext
		    .newInstance(CipherWrapper.class);
	    Unmarshaller um = context.createUnmarshaller();

	    File file = new File("Save2.xml");


	    // Reading XML from the file and unmarshalling.
	    CipherWrapper wrapper = (CipherWrapper) um.unmarshal(file);

	    wrapper.getPboxs().get(0).getX();

	} catch (Exception e) { // catches ANY exception
	    Alert alert = new Alert(AlertType.ERROR);
	    alert.setTitle("Error");
	    alert.setHeaderText("Could not load data");
	    alert.setContentText("Could not load data from file");

	    alert.showAndWait();
	}
    }
    
    public void saveAsXml(String filename) {
	try {
	    
	    JAXBContext context = JAXBContext.newInstance(SaveWrapper.class);
	    Marshaller m = context.createMarshaller();
	    m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
	    
	    
	    

	    File file = new File(filename);
	    m.marshal(saveWrapper, file);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
}
