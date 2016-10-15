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
 * @author Gigabyte
 */
public class SaveLoadTool {
    private CipherWrapper cipher = new CipherWrapper();
    
    public void AddProperties() {
	PropertiesWrapper props = new PropertiesWrapper();
	props.setNumberOfRounds("2");
	props.setBlockSize("64");
	props.setKeySize("16");
	props.setChainMode("counter");
	props.setPadding("Zero padding");
	props.setStartId("1");
	props.setEndId("2");
	cipher.setProperties(props);
    }
    public void AddProperties(String NumRounds, String BlockSize, String KeySize, String ChainMode, String Padding, String StartId, String EndId ) {
	PropertiesWrapper props = new PropertiesWrapper();
	props.setNumberOfRounds(NumRounds);
	props.setBlockSize(BlockSize);
	props.setKeySize(KeySize);
	props.setChainMode(ChainMode);
	props.setPadding(Padding);
	props.setStartId(StartId);
	props.setEndId(EndId);
    }
    
    public void AddPBoxs(List<PboxNode> pboxs) {
	List<pboxWrapper> convertedPBoxs = new ArrayList<pboxWrapper>();
		
	for (int i=0; i<pboxs.size(); i++) {
	    String outputData[];
	    outputData = pboxs.get(i).getOptions().getLookupTable().split(",");
	    
	    pboxWrapper pbox = new pboxWrapper();
	    pbox.setId(pboxs.get(i).getId());
	    pbox.setX(pboxs.get(i).getXString());
	    pbox.setY(pboxs.get(i).getYString());
	   
	    List<NodeLink> inputs = pboxs.get(i).getInConnections();
	    List<NodeLink> outputs = pboxs.get(i).getOutConnections();
	    List<input> wrapperInputs = new ArrayList<input>();
	    List<output> wrapperOutputs = new ArrayList<output>();
	    for (int j=0; j<inputs.size(); j++) {
	       input input = new input();
	       input.setConnectorID( inputs.get(j).getLinkID() );
	       input.setSize( Integer.parseInt( inputs.get(j).getConnectionSize() ) );
	       wrapperInputs.add(input);
	    }
	   
	    for (int j=0; j<outputs.size(); j++) {
		
		output output = new output();
		output.setConnectorID(outputs.get(j).getLinkID() );
		output.setSize( Integer.parseInt( outputs.get(j).getConnectionSize() ) );
		output.setOutputData(outputData[i]);
		wrapperOutputs.add(output);
	    }
	   
	    inputs finalInputs = new inputs();
	    Outputs finalOutputs = new Outputs();
	    
	    finalInputs.setInputs(wrapperInputs);
	    finalInputs.setNumInputs(wrapperInputs.size());
	    finalOutputs.setOutputs(wrapperOutputs);
	    finalOutputs.setNumOutputs(wrapperOutputs.size());
	    
	    pbox.setInputs(finalInputs);
	    pbox.setOutputs(finalOutputs);
	    
	    
	    
	    //pbox.setTable(     );
	   
	    convertedPBoxs.add(pbox);
	   
	}
	
	cipher.setPboxs(convertedPBoxs);	    
    }
    
    public void AddSBoxes(List<SboxNode> sboxs) {	
	List<sboxWrapper> convertedSBoxs = new ArrayList<sboxWrapper>();
	
	for (int i=0; i<sboxs.size(); i++) {
	    String outputData[];
	    outputData = sboxs.get(i).getOptions().getLookupTable().split(",\n");

	    
	    sboxWrapper sbox = new sboxWrapper();
	    sbox.setId(sboxs.get(i).getId());
	    sbox.setX(sboxs.get(i).getXString());
	    sbox.setY(sboxs.get(i).getYString());
	   
	   
	    List<NodeLink> inputs = sboxs.get(i).getInConnections();
	    List<NodeLink> outputs = sboxs.get(i).getOutConnections();
	    List<input> wrapperInputs = new ArrayList<input>();
	    List<output> wrapperOutputs = new ArrayList<output>();
	    for (int j=0; j<inputs.size(); j++) {
	       input input = new input();
	       input.setConnectorID( inputs.get(j).getLinkID() );
	       input.setSize( Integer.parseInt( inputs.get(j).getConnectionSize() ) );
	       wrapperInputs.add(input);
	    }
	   
	    for (int j=0; j<outputs.size(); j++) {
		output output = new output();
		output.setConnectorID(outputs.get(j).getLinkID() );
		output.setSize( Integer.parseInt( outputs.get(j).getConnectionSize() ) );
		wrapperOutputs.add(output);
	    }
	   
            System.out.println(sboxs.get(i).getOptions().getColumns());
            System.out.println(sboxs.get(i).getOptions().getRows());
	    int cols = Integer.parseInt(sboxs.get(i).getOptions().getColumns());
	    int rows = Integer.parseInt(sboxs.get(i).getOptions().getRows());
	    
	    Table sboxTable = new Table();
	    sboxTable.setCols(cols);
	    sboxTable.setRows(rows);
	    
	    List<Row> rowList = new ArrayList<Row>();
	    
	    for (int j=0; j<rows; j++) {
		Row row = new Row();
		row.setRowData(outputData[j]);
		rowList.add(row);
	    }
	    sboxTable.setRowData(rowList);

	    inputs finalInputs = new inputs();
	    Outputs finalOutputs = new Outputs();
	    
	    finalInputs.setInputs(wrapperInputs);
	    finalInputs.setNumInputs(wrapperInputs.size());
	    finalOutputs.setOutputs(wrapperOutputs);
	    finalOutputs.setNumOutputs(wrapperOutputs.size());
	    
	    sbox.setInputs(finalInputs);
	    sbox.setOutputs(finalOutputs);
	    sbox.setTable(sboxTable);
	   
	   convertedSBoxs.add(sbox);
	   
	}
	
	cipher.setSboxs(convertedSBoxs);
    }
    
    public void AddXors(List<XorNode> xors) {
	List<CipherXorWrapper> convertedXors = new ArrayList<CipherXorWrapper>();
	
	for (int i=0; i<xors.size(); i++) {
	    CipherXorWrapper xor = new CipherXorWrapper();
	    xor.setId(xors.get(i).getId());
	    xor.setX(xors.get(i).getXString());
	    xor.setY(xors.get(i).getYString());
	   
	    List<NodeLink> inputs = xors.get(i).getInConnections();
	    List<NodeLink> outputs = xors.get(i).getOutConnections();
	    List<input> wrapperInputs = new ArrayList<input>();
	    List<output> wrapperOutputs = new ArrayList<output>();
	    for (int j=0; j<inputs.size(); j++) {
	       input input = new input();
	       input.setConnectorID( inputs.get(j).getLinkID() );
	       input.setSize( Integer.parseInt( inputs.get(j).getConnectionSize() ) );
	       wrapperInputs.add(input);
	    }
	   
	    for (int j=0; j<outputs.size(); j++) {
		output output = new output();
		output.setConnectorID(outputs.get(j).getLinkID() );
		output.setSize( Integer.parseInt( outputs.get(j).getConnectionSize() ) );
		wrapperOutputs.add(output);
	    }
	   
	    inputs finalInputs = new inputs();
	    Outputs finalOutputs = new Outputs();
	    
	    finalInputs.setInputs(wrapperInputs);
	    finalInputs.setNumInputs(wrapperInputs.size());
	    finalOutputs.setOutputs(wrapperOutputs);
	    finalOutputs.setNumOutputs(wrapperOutputs.size());
	    
	    xor.setInputs(finalInputs);
	    xor.setOutputs(finalOutputs);
	   
	    convertedXors.add(xor);
	   
	}
	
	cipher.setXors(convertedXors);
    }
    
    public void AddConnections(List<NodeLink> connections) {
	List<CipherConnectionWrapper> convertedConnections = new ArrayList<CipherConnectionWrapper>();
		
	for (int i=0; i<connections.size(); i++) {
	    CipherConnectionWrapper connection = new CipherConnectionWrapper();
	    connection.setId(connections.get(i).getId());
	    
	    CipherConnectionFrom from = new CipherConnectionFrom();
	    CipherConnectionTo to = new CipherConnectionTo();
	    
	    from.setFromId(connections.get(i).getSourceId());
	  //  from.setConnectionPort(connections.get(i).g);
	    
	    to.setToId(connections.get(i).getTargetId());
	    
	    
	    connection.setTo(to);
	    connection.setFrom(from);

	   
	    convertedConnections.add(connection);
	}
	
	cipher.setConnections(convertedConnections);
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
	    
	    JAXBContext context = JAXBContext.newInstance(CipherWrapper.class);
	    Marshaller m = context.createMarshaller();
	    m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
	    
	    
	    

	    File file = new File(filename);
	    m.marshal(cipher, file);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
}
