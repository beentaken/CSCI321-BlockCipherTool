/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.util.List;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;

/**
 * @author Nick
 * @class wrapper for outputs so that they are stored in groups
 */
public class Outputs {
    private List<output> outputData;
    private int numOutputs;
    
    @XmlElement(name="output")
    public List<output> getOutputs() {
        return this.outputData;
    }
    
    public void setOutputs(List<output> Outputs) {
	this.outputData = Outputs;
    }
    
    @XmlAttribute(name="num")
    public int getNumOutputs() {
	return this.numOutputs;
    }
    
    public void setNumOutputs(int numOutputs) {
	this.numOutputs = numOutputs;
    }

}
