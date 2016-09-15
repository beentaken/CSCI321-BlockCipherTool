/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.util.List;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import blockciphertool.wrappers.input;
import blockciphertool.wrappers.output;

/**
 *
 * @author nick
 */
public class pboxWrapper {
    
    private List<input> inputs;
    private List<output> outputs;
    
    @XmlElementWrapper(name="inputs")
    @XmlElement(name="input")
    public List<input> getInputs() {
        return this.inputs;
    }
    
    public void setInputs(List<input> Inputs) {
	this.inputs = Inputs;
    }
    
    
    @XmlElementWrapper(name="outputs")
    @XmlElement(name="output")
    public List<output> getOutputs() {
        return this.outputs;
    }
    
    public void setOutputs(List<output> Outputs) {
	this.outputs = Outputs;
    }
    
}
