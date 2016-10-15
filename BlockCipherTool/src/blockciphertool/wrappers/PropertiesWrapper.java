/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.util.List;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;

import javax.xml.bind.annotation.XmlAttribute;

/**
 * @author nick
 * @class wrapper class for properties, used in encrypt and decrypt, and also stored as a top level xml element
 */
public class PropertiesWrapper {
    
    private String startId;
    private String endId;
    private String numberOfRounds;
    private String blockSize;
    private String keySize;
    private String chainMode;
    private String padding;
    
    @XmlElement(name="startID")
    public String getStartId() {
	return this.startId;
    }
    
    public void setStartId(String StartId) {
	this.startId = StartId;
    }
    
    @XmlElement(name="endID")
    public String getEndId() {
	return this.endId;
    }
    
    public void setEndId(String EndId) {
	this.endId = EndId;
    }
    
    @XmlElement(name="numberOfRounds")
    public String getNumberOfRounds() {
	return this.numberOfRounds;
    }
    
    public void setNumberOfRounds(String NumberOfRounds) {
	this.numberOfRounds = NumberOfRounds;
    }
    
    @XmlElement(name="blockSize")
    public String getBlockSize() {
	return this.blockSize;
    }
    
    public void setBlockSize(String BlockSize) {
	this.blockSize = BlockSize;
    }
    
    @XmlElement(name="keySize")
    public String getKeySize() {
	return this.keySize;
    }
    
    public void setKeySize(String KeySize) {
	this.keySize = KeySize;
    }
    
    @XmlElement(name="chainMode")
    public String getChainMode() {
	return this.chainMode;
    }
    
    public void setChainMode(String ChainMode) {
	this.chainMode = ChainMode;
    }
    
    @XmlElement(name="padding")
    public String getPadding() {
	return this.padding;
    }
    
    public void setPadding(String Padding) {
	this.padding = Padding;
    }
}
