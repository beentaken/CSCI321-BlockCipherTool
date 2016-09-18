/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.util.List;
import javax.xml.bind.annotation.XmlElement;

/**
 *
 * @author Gigabyte
 */
public class CipherFunctionWrapper {
    private String X;
    private String Y;
    private List<pboxWrapper> pboxs;
    private List<sboxWrapper> sboxs;
    private List<CipherXorWrapper> xors;
    private List<CipherConnectionWrapper> connections;
    
    @XmlElement(name="X")
    public String getX() {
        return this.X;
    }
    
    public void setX(String x) {
	this.X = x;
    }
    
    @XmlElement(name="Y")
    public String getY() {
        return this.Y;
    }
    
    public void setY(String y) {
	this.Y = y;
    }
    
    @XmlElement( name = "pbox")
    public List<pboxWrapper> getPboxs() {
        return pboxs;
    }
    public void setPboxs(List<pboxWrapper> pboxs) {
        this.pboxs = pboxs;
    }
    
    
    @XmlElement( name = "sbox")
    public List<sboxWrapper> getSboxs() {
        return sboxs;
    }
    public void setSboxs(List<sboxWrapper> sboxs) {
        this.sboxs = sboxs;
    }
    
    @XmlElement( name = "xor")
    public List<CipherXorWrapper> getXors() {
        return xors;
    }
    public void setXors(List<CipherXorWrapper> xors) {
        this.xors = xors;
    }
    
    @XmlElement(name="connection")
    public List<CipherConnectionWrapper> getConnections() {
        return this.connections;
    }
    
    public void setConnections(List<CipherConnectionWrapper> Connections) {
	this.connections = Connections;
    }
}
