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
public class Table {
    
    private List<Row> rowData;
    private int rows;
    private int cols;
    
    
    @XmlElement(name="rows")
    public List<Row> getRowData() {
        return this.rowData;
    }
    
    public void setRowData(List<Row> Rows) {
	this.rowData = Rows;
    }
    
    @XmlAttribute(name="rows")
    public int getRows() {
	return this.rows;
    }
    
    public void setRows(int Rows) {
	this.rows = Rows;
    }
    
    
    @XmlAttribute(name="cols")
    public int getCols() {
	return this.cols;
    }
    
    public void setCols(int Cols) {
	this.cols = Cols;
    }
    
    
}
