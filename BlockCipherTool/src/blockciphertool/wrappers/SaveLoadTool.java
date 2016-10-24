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
import blockciphertool.subKey;
import java.io.FileOutputStream;
import java.io.OutputStream;
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
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddProperties("1", "16", "16", "counter", "zero padding", "1", "2");
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddProperties("1", "16", "16", "counter", "zero padding", "1", "2");
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    
	}
    }
    
    public void AddPBoxs(String wrapperType, List<PboxNode> pboxs) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddPBoxs(pboxs);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddPBoxs(pboxs);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getKeygen();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddPBoxs(pboxs);
	    saveWrapper.setKeygenCipher(temp);
	}
    }
    
    public void AddSBoxes(String wrapperType, List<SboxNode> sboxs) {	
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddSBoxes(sboxs);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddSBoxes(sboxs);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getKeygen();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddSBoxes(sboxs);
	    saveWrapper.setKeygenCipher(temp);
	}
    }
    
    public void AddXors(String wrapperType, List<XorNode> xors) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddXors(xors);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddXors(xors);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getKeygen();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddXors(xors);
	    saveWrapper.setKeygenCipher(temp);
	}
    }
    
    public void AddConnections(String wrapperType, List<NodeLink> connections) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddConnections(connections);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddConnections(connections);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getKeygen();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddConnections(connections);
	    saveWrapper.setKeygenCipher(temp);
	}
    }

    public void AddSubkeys(String wrapperType, List<subKey> subkeys) {
	if ( wrapperType.equals( "encrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getEncryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddKeys(subkeys);
	    saveWrapper.setEncryptionCipher(temp);
	} else if( wrapperType.equals( "decrypt" ) ) {
	    CipherWrapper temp = saveWrapper.getDecryptionCipher();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddKeys(subkeys);
	    saveWrapper.setDecryptionCipher(temp);
	} else if( wrapperType.equals( "keygen" ) ) {
	    CipherWrapper temp = saveWrapper.getKeygen();
	    if (temp == null) {
		temp = new CipherWrapper();
	    }
	    temp.AddKeys(subkeys);
	    saveWrapper.setKeygenCipher(temp);
	}
	
    }
    
    public void AddProperties(PropertiesWrapper Properties) {
	this.saveWrapper.setProperties(Properties);
    }
    
    public void AddProperties(String NumRounds, String BlockSize, String KeySize, String ChainMode, String Padding, String StartId, String EndId ) {
	PropertiesWrapper properties = this.saveWrapper.getProperties();
	properties.setNumberOfRounds(NumRounds);
	properties.setBlockSize(BlockSize);
	properties.setKeySize(KeySize);
	properties.setChainMode(ChainMode);
	properties.setPadding(Padding);
	properties.setStartId(StartId);
	properties.setEndId(EndId);
	this.saveWrapper.setProperties(properties);
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
	    
	    JAXBContext context = JAXBContext.newInstance("blockciphertool.wrappers");
	    Marshaller m = context.createMarshaller();
	    m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
	    
	    
	    
	    File file = new File(filename);
	    OutputStream os = new FileOutputStream(file);

	    
	    m.marshal(saveWrapper.getEncryptionWrappedCipher(), os);
	    m.marshal(saveWrapper.getDecryptionWrappedCipher(), os);
	    m.marshal(saveWrapper.getWrappedKeygen(), os);
	    m.marshal(saveWrapper.getProperties(), os);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
    public void saveMultipleAsXml(String encryptFilename, String decryptFilename, String keygenFilename, String PropertiesFilename) {
	try {
	    
	    JAXBContext context = JAXBContext.newInstance("blockciphertool.wrappers");
	    Marshaller m = context.createMarshaller();
	    m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
	    
	    
	    
	    File encryptFile = new File(encryptFilename);
	    File decryptFile = new File(decryptFilename);
	    File keygenFile = new File(keygenFilename);
	    File propertiesFile = new File(PropertiesFilename);
	    
	    

	    
	    m.marshal(saveWrapper.getEncryptionWrappedCipher(), encryptFile);
	    m.marshal(saveWrapper.getDecryptionWrappedCipher(), decryptFile);
	    m.marshal(saveWrapper.getWrappedKeygen(), keygenFile);
	    m.marshal(saveWrapper.getProperties(), propertiesFile);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
}
