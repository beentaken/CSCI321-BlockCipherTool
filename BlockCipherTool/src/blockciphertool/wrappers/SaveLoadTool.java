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
    
    public void saveAsXml(String filename) {
	try {
	    
	    JAXBContext context = JAXBContext.newInstance(CipherWrapper.class);
	    Marshaller m = context.createMarshaller();
	    m.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
	    
	    CipherWrapper wrapper = new CipherWrapper();
	    
	    //inputs
	    input input1 = new input();
	    input input2 = new input();
 
	    input1.setConnectorID("1");
	    input1.setSize("32");
	    input2.setConnectorID("2");
	    input2.setSize("64");
	    
	    //outputs
	    output output1 = new output();
	    output output2 = new output();
 
	    output1.setConnectorID("1");
	    output1.setSize("32");
	    output2.setConnectorID("2");
	    output2.setSize("64");
	    
	    
	    //pboxs
	    List<input> pbox1Inputs = new ArrayList<input>();
	    List<output> pbox1Outputs = new ArrayList<output>();
	   
	    pbox1Inputs.add(input1);
	    pbox1Inputs.add(input2);
	    pbox1Outputs.add(output1);
	    
	    pboxWrapper pbox1 = new pboxWrapper();
	    
	    pbox1.setInputs(pbox1Inputs);
	    pbox1.setOutputs(pbox1Outputs);
	    pbox1.setX("100");
	    pbox1.setY("200");
	    pbox1.setId("1");
	    
	    List<pboxWrapper> pboxs = new ArrayList<pboxWrapper>();
	    pboxs.add(pbox1);
	    
	    	    
	    //sboxs
	    List<input> sbox1Inputs = new ArrayList<input>();
	    List<output> sbox1Outputs = new ArrayList<output>();
	    
	    sbox1Inputs.add(input1);
	    sbox1Inputs.add(input2);
	    sbox1Outputs.add(output1);
	    
	    sboxWrapper sbox1 = new sboxWrapper();
	    
	    sbox1.setInputs(sbox1Inputs);
	    sbox1.setOutputs(sbox1Outputs);
	    sbox1.setX("100");
	    sbox1.setY("200");
	    sbox1.setId("1");

	    List<sboxWrapper> sboxs = new ArrayList<sboxWrapper>();
	    sboxs.add(sbox1);
	   
	    
	    //XORS
	    CipherXorWrapper xor1 = new CipherXorWrapper();
	    
	    xor1.setInputs(sbox1Inputs);
	    xor1.setOutputs(sbox1Outputs);
	    xor1.setY("150");
	    xor1.setX("980");
	    xor1.setId("3");
	    xor1.setSize("8");
	    
	    List<CipherXorWrapper> xors = new ArrayList<CipherXorWrapper>();
	    xors.add(xor1);
	    
	    
	    //Connections
	    CipherConnectionWrapper connection = new CipherConnectionWrapper();
	    CipherConnectionFrom from = new CipherConnectionFrom();
	    CipherConnectionTo to = new CipherConnectionTo();
	    
	    from.setConnectionBox("1");
	    from.setConnectionPort("2");
	    from.setFromId("3");
	    
	    to.setConnectionBox("2");
	    to.setConnectionPort("1");
	    to.setToId("2");

	    connection.setFrom(from);
	    connection.setTo(to);
	    connection.setId("5");
	    
	    List<CipherConnectionWrapper> connections = new ArrayList<CipherConnectionWrapper>();
	    connections.add(connection);
	    
	    
	    //function
	    CipherFunctionWrapper function1 = new CipherFunctionWrapper();
	    function1.setConnections(connections);
	    function1.setPboxs(pboxs);
	    function1.setSboxs(sboxs);
	    function1.setX("500");
	    function1.setY("700");
	    function1.setXors(xors);
	    
	    List<CipherFunctionWrapper> functions = new ArrayList<CipherFunctionWrapper>();
	    functions.add(function1);
	    
	    
	    //setting wrapper
	    wrapper.setPboxs(pboxs);
	    wrapper.setSboxs(sboxs);
	    wrapper.setXors(xors);
	    wrapper.setConnections(connections);
	    wrapper.setFunctions(functions);
	    
	    File file = new File("Save1.xml");
	    m.marshal(wrapper, file);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
}
