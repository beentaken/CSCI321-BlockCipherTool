/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.*;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableColumn.CellEditEvent;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javax.swing.ProgressMonitorInputStream;

/**
 *
 * @author Alex
 */
public class XorOptions extends AnchorPane{
    
    @FXML private TextField xorSize;
    @FXML private TableView<connection> inputTable;
    @FXML private TableView<connection> outputTable;
    @FXML private TableColumn<connection, String> InputIds;
    @FXML private TableColumn<connection, String> OutputIds;
    @FXML private TableColumn<connection, String> InputIdSizes;
    @FXML private TableColumn<connection, String> OutputIdSizes;
    
    @FXML Button cancel;
    
    private String xorSizeData;
    
    private final ObservableList<connection> dataIn = FXCollections.observableArrayList();
    private final ObservableList<connection> dataOut = FXCollections.observableArrayList();
    
    private List<NodeLink> inNodeLinks;
    private List<NodeLink> outNodeLinks;
    
    public XorOptions() {
        
        System.out.println("blockciphertool.PboxOptions.PboxOptions()");
    }
    
    public void loadData(List <NodeLink> inLinks, List<NodeLink> outLinks) {
        
        if (xorSizeData != null)
            xorSize.setText(xorSizeData);
        
	dataIn.clear();
        dataOut.clear();
        connection conn;

	for (int i=0; i< inLinks.size(); i++) {
            conn = new connection();
            conn.setLinkNum(i+1);
	    
	    if ( inLinks.get(i).getConnectionSize() == null ) {
		conn.setSize("0");

	    } else {
		conn.setSize( inLinks.get(i).getConnectionSize() );

	    }
            dataIn.add(conn);	    
	}
        
        for (int i=0; i< outLinks.size(); i++) {
            conn = new connection();
            conn.setLinkNum(i+1);
	    
	    if ( outLinks.get(i).getConnectionSize() == null ) {
		conn.setSize("0");

	    } else {
		conn.setSize( outLinks.get(i).getConnectionSize() );

	    }
            dataOut.add(conn);	    
	}
	
        inputTable.setEditable(true);
        outputTable.setEditable(true);
        
        InputIds.setCellValueFactory(new PropertyValueFactory<connection, String>("linknum"));
        InputIdSizes.setCellValueFactory(new PropertyValueFactory<connection, String>("size"));
        InputIdSizes.setCellFactory(TextFieldTableCell.forTableColumn());
        
        OutputIds.setCellValueFactory(new PropertyValueFactory<connection, String>("linknum"));
        OutputIdSizes.setCellValueFactory(new PropertyValueFactory<connection, String>("size"));
        OutputIdSizes.setCellFactory(TextFieldTableCell.forTableColumn());
        
        InputIdSizes.setOnEditCommit(
            new EventHandler<CellEditEvent<connection, String>>() {
                @Override
                public void handle(CellEditEvent<connection, String> t) {
                    ((connection) t.getTableView().getItems().get(
                            t.getTablePosition().getRow())
                            ).setSize(t.getNewValue());
                }
            }
        );
        inputTable.setItems(dataIn);

        OutputIdSizes.setOnEditCommit(
            new EventHandler<CellEditEvent<connection, String>>() {
                @Override
                public void handle(CellEditEvent<connection, String> t) {
                    ((connection) t.getTableView().getItems().get(
                            t.getTablePosition().getRow())
                            ).setSize(t.getNewValue());
                }
            }
        );
        outputTable.setItems(dataOut);
        
        inNodeLinks = inLinks;
        outNodeLinks = outLinks;
    }
    
    public void setData(String Datasize) {
        xorSizeData = Datasize;
    }
    
    public static class connection {
 
        private SimpleIntegerProperty linknum;
        private SimpleStringProperty size;
 
        private connection() {
            this.linknum = new SimpleIntegerProperty(0);
            this.size = new SimpleStringProperty("");
        }
                
        private connection(int templinknum, String tempsize) {
            this.linknum = new SimpleIntegerProperty(templinknum);
            this.size = new SimpleStringProperty(tempsize);
        }
 
        public int getLinknum() {
            return linknum.get();
        }
 
        public void setLinkNum(int lnum) {
            linknum.set(lnum);
        }
 
        public String getSize() {
            return size.get();
        }
 
        public void setSize(String lsize) {
            size.set(lsize);
        }
    }
    
    @FXML
    private void save() {
        xorSizeData = xorSize.getText();
        
        for (int i=0; i<inNodeLinks.size();i++) {
            inNodeLinks.get(i).setSize(dataIn.get(i).getSize());
        }
        for (int i=0; i<outNodeLinks.size();i++) {
            outNodeLinks.get(i).setSize(dataOut.get(i).getSize());
        }
        
        Stage stage = (Stage) cancel.getScene().getWindow();
        stage.close();
    }
    
    @FXML
    private void cancel() {
        Stage stage = (Stage) cancel.getScene().getWindow();
        stage.close();
    }
}

