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
	    
	    
	    input input1 = new input();
	    input input2 = new input();
 
	    input1.setConnectorID("1");
	    input1.setSize("32");
	    input2.setConnectorID("2");
	    input2.setSize("64");
	    
	    output output1 = new output();
	    output output2 = new output();
 
	    output1.setConnectorID("1");
	    output1.setSize("32");
	    output2.setConnectorID("2");
	    output2.setSize("64");
	    
	    
	    List<input> pbox1Inputs = new ArrayList<input>();
	    List<input> pbox2Inputs = new ArrayList<input>();
	    List<output> pbox1Outputs = new ArrayList<output>();
	    List<output> pbox2Outputs = new ArrayList<output>();
	    
	    
	    pbox1Inputs.add(input1);
	    pbox1Inputs.add(input2);
	    pbox1Outputs.add(output1);
	    pbox2Inputs.add(input1);
	    pbox2Inputs.add(input2);
	    pbox2Outputs.add(output2);

	    
	    
	  

	    
	    pboxWrapper pbox1 = new pboxWrapper();
	    pboxWrapper pbox2 = new pboxWrapper();
	    
	    pbox1.setInputs(pbox1Inputs);
	    pbox1.setOutputs(pbox1Outputs);
	    pbox2.setInputs(pbox2Inputs);
	    pbox2.setOutputs(pbox2Outputs);

	    
	    List<pboxWrapper> pboxs = new ArrayList<pboxWrapper>();

	    pboxs.add(pbox1);
	    pboxs.add(pbox2);
	    
	    wrapper.setPboxs(pboxs);
	    
	    File file = new File("Save1.xml");
	    m.marshal(wrapper, file);
	    	    
	} catch (Exception e) {
	    e.printStackTrace();
	}
    }
    
}
