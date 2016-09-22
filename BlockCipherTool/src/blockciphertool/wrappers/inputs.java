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
 *
 * @author Gigabyte
 */
public class inputs {
    private List<input> inputData;
    private int numInputs;
    
    @XmlElement(name="input")
    public List<input> getInputs() {
        return this.inputData;
    }
    
    public void setInputs(List<input> Inputs) {
	this.inputData = Inputs;
    }
    
    
    @XmlAttribute(name="num")
    public int getNumInputs() {
	return this.numInputs;
    }
    
    public void setNumInputs(int NumInputs) {
	this.numInputs = NumInputs;
    }

}
