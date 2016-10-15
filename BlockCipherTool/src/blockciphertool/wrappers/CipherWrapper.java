/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool.wrappers;

import java.util.List;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;


/**
 * @author Nick
 * @Class save wrapper class for an encryption, decryption or key cipher
 */
@XmlRootElement(name = "cipher")
public class CipherWrapper {
 
    private List<pboxWrapper> pboxs;
    private List<sboxWrapper> sboxs;
    private List<CipherFunctionWrapper> functions;
    private List<CipherXorWrapper> xors;
    private List<CipherConnectionWrapper> connections;
    private List<CipherKeyWrapper> keys;
    
    private PropertiesWrapper properties;
    
    @XmlElement( name = "properties" )
    public PropertiesWrapper getProperties() {
        return this.properties;
    }
    public void setProperties(PropertiesWrapper Properties) {
        this.properties = Properties;
    }
    
    
    @XmlElement( name = "pbox" )
    public List<pboxWrapper> getPboxs() {
        return this.pboxs;
    }
    public void setPboxs(List<pboxWrapper> pboxs) {
        this.pboxs = pboxs;
    }
    
    
    @XmlElement( name = "sbox" )
    public List<sboxWrapper> getSboxs() {
        return this.sboxs;
    }
    public void setSboxs(List<sboxWrapper> sboxs) {
        this.sboxs = sboxs;
    }
    
    
    @XmlElement( name = "function")
    public List<CipherFunctionWrapper> getFunctions() {
        return this.functions;
    }
    public void setFunctions(List<CipherFunctionWrapper> functions) {
        this.functions = functions;
    }
    
    
    @XmlElement( name = "xor" )
    public List<CipherXorWrapper> getXors() {
        return this.xors;
    }
    public void setXors(List<CipherXorWrapper> xors) {
        this.xors = xors;
    }
    
    
    @XmlElement( name = "connection" )
    public List<CipherConnectionWrapper> getConnections() {
        return this.connections;
    }
    public void setConnections(List<CipherConnectionWrapper> connections) {
        this.connections = connections;
    }
    
    @XmlElement( name = "keys" )
    public List<CipherKeyWrapper> getKeys() {
	return this.keys;
    }
    
    public void setKeys(List<CipherKeyWrapper> Keys) {
	this.keys = Keys;
    }

}