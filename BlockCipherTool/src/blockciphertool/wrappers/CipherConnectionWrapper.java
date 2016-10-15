/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;

/**
 * @author Nick
 * @class wrapper class for connections, containing both a connection from and connection to
 */
public class CipherConnectionWrapper {
    private String id;
    private CipherConnectionTo to;
    private CipherConnectionFrom from;
    
    @XmlAttribute(name="ID")
    public String getId() {
        return this.id;
    }
    
    public void setId(String Id) {
	this.id = Id;
    }
    
    @XmlElement(name="to")
    public CipherConnectionTo getTo() {
        return this.to;
    }
    
    public void setTo(CipherConnectionTo To) {
	this.to = To;
    }
    
    @XmlElement(name="from")
    public CipherConnectionFrom getFrom() {
        return this.from;
    }
    
    public void setFrom(CipherConnectionFrom From) {
	this.from = From;
    }
}
