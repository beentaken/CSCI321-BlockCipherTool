/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.Marshaller;

/**
 *
 * @author Gigabyte
 */
public class SaveLoadTool {
    

    public void saveAsXml(String filename, CipherWrapper wrapper) {
	try {
	    
	    JAXBContext context = JAXBContext.newInstance(CipherWrapper.class);
	    Marshaller m = context.createMarshaller();
	    m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
	    
	    
	    
	    /*
	    //pbox 2 table
	    Row pbox2row1 = new Row();
	    Row pbox2row2 = new Row();
	    Row pbox2row3= new Row();
	    Row pbox2row4 = new Row();
	    Row pbox2row5 = new Row();
	
	   
	    pbox2row1.setRowData(" 2  , 0 , 1 ");
	    pbox2row2.setRowData(" 00 , 00, 01 ");
	    pbox2row3.setRowData(" 01 , 00, 00 ");
	    pbox2row4.setRowData(" 10 , 00, 10 ");
	    pbox2row5.setRowData(" 11 , 00, 11 ");
	    

	    
	    List<Row> pbox2rows = new ArrayList<Row>();
	    pbox2rows.add(pbox2row1);
	    pbox2rows.add(pbox2row2);
	    
	    Table pbox2table = new Table();
	    pbox2table.setRowData(pbox2rows);
	    pbox2table.setRows(5);
	    pbox2table.setCols(3);

	    //sbox 4 table

	    
	    List<Row> sbox4rows = new ArrayList<Row>();
	    sbox4rows.add(pbox2row1);
	    sbox4rows.add(pbox2row2);
	    sbox4rows.add(pbox2row3);
	    sbox4rows.add(pbox2row4);
	    sbox4rows.add(pbox2row5);
	    
	    Table sbox4table = new Table();
	    sbox4table.setRowData(sbox4rows);
	    sbox4table.setRows(5);
	    sbox4table.setCols(3);

	    
	    //pbox 5 Table	    
	    List<Row> pbox5rows = new ArrayList<Row>();
	    pbox5rows.add(pbox2row1);
	    pbox5rows.add(pbox2row2);
	    pbox5rows.add(pbox2row3);
	    pbox5rows.add(pbox2row4);
	    pbox5rows.add(pbox2row5);
	    
	    Table pbox5table = new Table();
	    pbox5table.setRowData(pbox5rows);
	    pbox5table.setRows(5);
	    pbox5table.setCols(3);

	    
	    
	    //PBOXS
	    //pbox 1
	    //inputs
	    input pbox1input1 = new input();
 
	    pbox1input1.setConnectorID("0");
	    pbox1input1.setSize(4);
	    
	    //outputs
	    output pbox1output1 = new output();
	    output pbox1output2 = new output();
 
	    pbox1output1.setConnectorID("1");
	    pbox1output1.setSize(2);
	    pbox1output2.setConnectorID("2");
	    pbox1output2.setSize(2);
	    
	    List<input> pbox1Inputs = new ArrayList<input>();
	    List<output> pbox1Outputs = new ArrayList<output>();
	   
	    pbox1Inputs.add(pbox1input1);
	    pbox1Outputs.add(pbox1output1);
	    pbox1Outputs.add(pbox1output2);
	    
	    inputs pbox1InputsWrap = new inputs();
	    Outputs pbox1OutputsWrap = new Outputs();
	    pbox1InputsWrap.setInputs(pbox1Inputs);
	    pbox1OutputsWrap.setOutputs(pbox1Outputs);
	    pbox1InputsWrap.setNumInputs(pbox1Inputs.size());
	    pbox1OutputsWrap.setNumOutputs(pbox1Outputs.size());
	    
	    pboxWrapper pbox1 = new pboxWrapper();
	    pbox1.setInputs(pbox1InputsWrap);
	    pbox1.setOutputs(pbox1OutputsWrap);
	    pbox1.setX("240");
	    pbox1.setY("468");
	    pbox1.setId("1");
	    
	    
	    //PBOX2
	    //inputs
	    input pbox2input1 = new input();
 
	    pbox2input1.setConnectorID("1");
	    pbox2input1.setSize(2);
	    
	    //outputs
	    output pbox2output1 = new output();
 
	    pbox2output1.setConnectorID("3");
	    pbox2output1.setSize(3);

	    List<input> pbox2Inputs = new ArrayList<input>();
	    List<output> pbox2Outputs = new ArrayList<output>();
	   
	    pbox2Inputs.add(pbox2input1);
	    pbox2Outputs.add(pbox2output1);
	    
	    inputs pbox2InputsWrap = new inputs();
	    Outputs pbox2OutputsWrap = new Outputs();
	    pbox2InputsWrap.setInputs(pbox2Inputs);
	    pbox2OutputsWrap.setOutputs(pbox2Outputs);
	    pbox2InputsWrap.setNumInputs(pbox2Inputs.size());
	    pbox2OutputsWrap.setNumOutputs(pbox2Outputs.size());
	    
	    pboxWrapper pbox2 = new pboxWrapper();
	    pbox2.setInputs(pbox2InputsWrap);
	    pbox2.setOutputs(pbox2OutputsWrap);
	    pbox2.setTable(sbox4table);
	    pbox2.setX("500");
	    pbox2.setY("500");
	    pbox2.setId("2");



	    //PBOX5
	    //inputs
	    input pbox5input1 = new input();
 
	    pbox5input1.setConnectorID("5");
	    pbox5input1.setSize(2);
	    
	    //outputs
	    output pbox5output1 = new output();
 
	    pbox5output1.setConnectorID("6");
	    pbox5output1.setSize(2);

	    List<input> pbox5Inputs = new ArrayList<input>();
	    List<output> pbox5Outputs = new ArrayList<output>();
	   
	    pbox5Inputs.add(pbox5input1);
	    pbox5Outputs.add(pbox5output1);
	    
	    inputs pbox5InputsWrap = new inputs();
	    Outputs pbox5OutputsWrap = new Outputs();
	    pbox5InputsWrap.setInputs(pbox5Inputs);
	    pbox5OutputsWrap.setOutputs(pbox5Outputs);
	    pbox5InputsWrap.setNumInputs(pbox5Inputs.size());
	    pbox5OutputsWrap.setNumOutputs(pbox5Outputs.size());
	    
	    pboxWrapper pbox5 = new pboxWrapper();
	    pbox5.setInputs(pbox5InputsWrap);
	    pbox5.setOutputs(pbox5OutputsWrap);
	    pbox5.setTable(pbox5table);
	    pbox5.setX("600");
	    pbox5.setY("600");
	    pbox5.setId("5");


	    //pbox 7
	    //inputs
	    input pbox7input1 = new input();
	    input pbox7input2 = new input();
 
	    pbox7input1.setConnectorID("6");
	    pbox7input1.setSize(2);
	    pbox7input2.setConnectorID("2");
	    pbox7input2.setSize(2);
	    
	    
	    //outputs
	    output pbox7output1 = new output();
 
	    pbox7output1.setConnectorID("7");
	    pbox7output1.setSize(4);

	    
	    List<input> pbox7Inputs = new ArrayList<input>();
	    List<output> pbox7Outputs = new ArrayList<output>();
	   
	    pbox7Inputs.add(pbox7input1);
	    pbox7Inputs.add(pbox7input2);
	    pbox7Outputs.add(pbox7output1);
	    
	    inputs pbox7InputsWrap = new inputs();
	    Outputs pbox7OutputsWrap = new Outputs();
	    pbox7InputsWrap.setInputs(pbox7Inputs);
	    pbox7OutputsWrap.setOutputs(pbox7Outputs);
	    pbox7InputsWrap.setNumInputs(pbox7Inputs.size());
	    pbox7OutputsWrap.setNumOutputs(pbox7Outputs.size());
	    
	    pboxWrapper pbox7 = new pboxWrapper();
	    pbox7.setInputs(pbox7InputsWrap);
	    pbox7.setOutputs(pbox7OutputsWrap);
	    pbox7.setX("240");
	    pbox7.setY("468");
	    pbox7.setId("7");

	    
	    //SBOXS
	    //sbox4
	    //inputs
	    input sbox4input1 = new input();
 
	    sbox4input1.setConnectorID("4");
	    sbox4input1.setSize(3);
	    
	    //outputs
	    output sbox4output1 = new output();
 
	    sbox4output1.setConnectorID("5");
	    sbox4output1.setSize(2);

	    List<input> sbox4Inputs = new ArrayList<input>();
	    List<output> sbox4Outputs = new ArrayList<output>();
	   
	    sbox4Inputs.add(sbox4input1);
	    sbox4Outputs.add(sbox4output1);
	    
	    inputs sbox4InputsWrap = new inputs();
	    Outputs sbox4OutputsWrap = new Outputs();
	    sbox4InputsWrap.setInputs(sbox4Inputs);
	    sbox4OutputsWrap.setOutputs(sbox4Outputs);
	    sbox4InputsWrap.setNumInputs(sbox4Inputs.size());
	    sbox4OutputsWrap.setNumOutputs(sbox4Outputs.size());
	    
	    sboxWrapper sbox4 = new sboxWrapper();
	    sbox4.setInputs(sbox4InputsWrap);
	    sbox4.setOutputs(sbox4OutputsWrap);
	    sbox4.setTable(sbox4table);
	    sbox4.setX("700");
	    sbox4.setY("700");
	    sbox4.setId("4");
	    
	    
	    //XORS
	    //xor1
	    //inputs
	    input xor3input1 = new input();
	    input xor3input2 = new input();
 
	    xor3input1.setConnectorID("3");
	    xor3input1.setSize(3);
	    xor3input2.setConnectorID("k");
	    xor3input2.setSize(3);
	    //outputs
	    output xor3output1 = new output();
 
	    xor3output1.setConnectorID("4");
	    xor3output1.setSize(3);

	    List<input> xor3Inputs = new ArrayList<input>();
	    List<output> xor3Outputs = new ArrayList<output>();
	   
	    xor3Inputs.add(xor3input1);
	    xor3Inputs.add(xor3input2);
	    xor3Outputs.add(xor3output1);
	    
	    inputs xor3InputsWrap = new inputs();
	    Outputs xor3OutputsWrap = new Outputs();
	    xor3InputsWrap.setInputs(xor3Inputs);
	    xor3OutputsWrap.setOutputs(xor3Outputs);
	    xor3InputsWrap.setNumInputs(xor3Inputs.size());
	    xor3OutputsWrap.setNumOutputs(xor3Outputs.size());
	    
	    CipherXorWrapper xor3 = new CipherXorWrapper();
	    xor3.setInputs(xor3InputsWrap);
	    xor3.setOutputs(xor3OutputsWrap);
	    xor3.setX("300");
	    xor3.setY("300");
	    xor3.setId("3");
	    
	    
	    //xor2
	    //inputs
	    input xor6input1 = new input();
	    input xor6input2 = new input();
 
	    xor6input1.setConnectorID("6");
	    xor6input1.setSize(2);
	    xor6input2.setConnectorID("2");
	    xor6input2.setSize(2);
	    //outputs
	    output xor6output1 = new output();
 
	    xor6output1.setConnectorID("7");
	    xor6output1.setSize(2);

	    List<input> xor6Inputs = new ArrayList<input>();
	    List<output> xor6Outputs = new ArrayList<output>();
	   
	    xor6Inputs.add(xor6input1);
	    xor6Inputs.add(xor6input2);
	    xor6Outputs.add(xor6output1);
	    
	    inputs xor6InputsWrap = new inputs();
	    Outputs xor6OutputsWrap = new Outputs();
	    xor6InputsWrap.setInputs(xor6Inputs);
	    xor6OutputsWrap.setOutputs(xor6Outputs);
	    xor6InputsWrap.setNumInputs(xor6Inputs.size());
	    xor6OutputsWrap.setNumOutputs(xor6Outputs.size());
	    
	    CipherXorWrapper xor6 = new CipherXorWrapper();
	    xor6.setInputs(xor6InputsWrap);
	    xor6.setOutputs(xor6OutputsWrap);
	    xor6.setX("200");
	    xor6.setY("200");
	    xor6.setId("6");
	    
	    
	    //functions
	    //function 8
	    CipherFunctionWrapper function8 = new CipherFunctionWrapper();
	    List<pboxWrapper> pboxs = new ArrayList<pboxWrapper>();
	    pboxs.add(pbox2);
	    pboxs.add(pbox5);
	    List<CipherXorWrapper> xors = new ArrayList<CipherXorWrapper>();
	    xors.add(xor3);
	    List<sboxWrapper> sboxs = new ArrayList<sboxWrapper>();
	    sboxs.add(sbox4);
	    
	    function8.setPboxs(pboxs);
	    function8.setSboxs(sboxs);
	    function8.setXors(xors);
	    function8.setX("900");
	    function8.setY("900");
	    function8.setId("8");
	    
	    PropertiesWrapper properties = new PropertiesWrapper();
	    properties.setBlockSize("7");
	    properties.setStartId("1");
	    properties.setEndId("7");
	    properties.setKeySize("4");
	    properties.setNumberOfRounds("9");
	    
	    //Cipher
	    List<CipherXorWrapper> cipherXors = new ArrayList<CipherXorWrapper>();
	    cipherXors.add(xor6);
	    List<pboxWrapper> cipherPboxs = new ArrayList<pboxWrapper>();
	    cipherPboxs.add(pbox1);
	    cipherPboxs.add(pbox7);
	    List<sboxWrapper> cipherSboxs = new ArrayList<sboxWrapper>();
	    
	    
	    List<CipherFunctionWrapper> cipherFunctions = new ArrayList<CipherFunctionWrapper>();
	    cipherFunctions.add(function8);
	    
	    
	    //setting wrapper
	    wrapper.setPboxs(cipherPboxs);
	    wrapper.setSboxs(cipherSboxs);
	    wrapper.setXors(cipherXors);
	    wrapper.setFunctions(cipherFunctions);
	    wrapper.setProperties(properties);
	    */
	    File file = new File("Save1.xml");
	    m.marshal(wrapper, file);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
}
