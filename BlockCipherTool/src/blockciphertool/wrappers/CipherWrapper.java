/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import blockciphertool.NodeLink;
import blockciphertool.PboxNode;
import blockciphertool.SboxNode;
import blockciphertool.XorNode;
import blockciphertool.subKey;
import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


/**
 * @author Nick
 * @Class save wrapper class for an encryption, decryption or key cipher
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "cipherWrapper", propOrder = {"pboxs", "sboxs", "functions", "xors", "connections", "keys", "properties"})
public class CipherWrapper {
 
    private List<pboxWrapper> pboxs = new ArrayList<pboxWrapper>();
    private List<sboxWrapper> sboxs = new ArrayList<sboxWrapper>();
    private List<CipherFunctionWrapper> functions = new ArrayList<CipherFunctionWrapper>();
    private List<CipherXorWrapper> xors = new ArrayList<CipherXorWrapper>();
    private List<CipherConnectionWrapper> connections = new ArrayList<CipherConnectionWrapper>();
    private List<CipherSubkeyWrapper> keys = new ArrayList<CipherSubkeyWrapper>();
    
    private PropertiesWrapper properties = new PropertiesWrapper();
    
    
    
    public PropertiesWrapper getProperties() {
        return this.properties;
    }
    public void setProperties(PropertiesWrapper Properties) {
        this.properties = Properties;
    }
    
    
    public List<pboxWrapper> getPboxs() {
        return this.pboxs;
    }
    public void setPboxs(List<pboxWrapper> pboxs) {
        this.pboxs = pboxs;
    }
    
    
    public List<sboxWrapper> getSboxs() {
        return this.sboxs;
    }
    public void setSboxs(List<sboxWrapper> sboxs) {
        this.sboxs = sboxs;
    }
    
    
    public List<CipherFunctionWrapper> getFunctions() {
        return this.functions;
    }
    public void setFunctions(List<CipherFunctionWrapper> functions) {
        this.functions = functions;
    }
    
    
    public List<CipherXorWrapper> getXors() {
        return this.xors;
    }
    public void setXors(List<CipherXorWrapper> xors) {
        this.xors = xors;
    }
    
    
    public List<CipherConnectionWrapper> getConnections() {
        return this.connections;
    }
    public void setConnections(List<CipherConnectionWrapper> connections) {
        this.connections = connections;
    }
    
    public List<CipherSubkeyWrapper> getKeys() {
	return this.keys;
    }
    
    public void setKeys(List<CipherSubkeyWrapper> Keys) {
	this.keys = Keys;
    }

    
    
    
    public void AddProperties() {
	properties.setNumberOfRounds("2");
	properties.setBlockSize("64");
	properties.setKeySize("16");
	properties.setChainMode("counter");
	properties.setPadding("Zero padding");
	properties.setStartId("1");
	properties.setEndId("2");
    }
    public void AddProperties(String NumRounds, String BlockSize, String KeySize, String ChainMode, String Padding, String StartId, String EndId ) {
	properties.setNumberOfRounds(NumRounds);
	properties.setBlockSize(BlockSize);
	properties.setKeySize(KeySize);
	properties.setChainMode(ChainMode);
	properties.setPadding(Padding);
	properties.setStartId(StartId);
	properties.setEndId(EndId);
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
	
	setPboxs(convertedPBoxs);	    
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
	
	setSboxs(convertedSBoxs);
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
	
	setXors(convertedXors);
    }

    public void AddKeys(List<subKey> subkeys) {
	List<CipherSubkeyWrapper> convertedSubkeys = new ArrayList<CipherSubkeyWrapper>();
	
	for (int i=0; i<subkeys.size(); i++) {
	    CipherSubkeyWrapper subkey = new CipherSubkeyWrapper();
	    subkey.setId(subkeys.get(i).getId());
	    subkey.setX(subkeys.get(i).getXString());
	    subkey.setY(subkeys.get(i).getYString());
	   
	    List<NodeLink> inputs = subkeys.get(i).getInConnections();
	    List<input> wrapperInputs = new ArrayList<input>();
	    for (int j=0; j<inputs.size(); j++) {
	       input input = new input();
	       input.setConnectorID( inputs.get(j).getLinkID() );
	       input.setSize( Integer.parseInt( inputs.get(j).getConnectionSize() ) );
	       wrapperInputs.add(input);
	    }
	   
	    inputs finalInputs = new inputs();
	    
	    finalInputs.setInputs(wrapperInputs);
	    finalInputs.setNumInputs(wrapperInputs.size());

	    
	    subkey.setInputs(finalInputs);
	   
	    convertedSubkeys.add(subkey);
	   
	}
	
	setKeys(convertedSubkeys);
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
	
	setConnections(convertedConnections);
    }

    
    
    
    
}