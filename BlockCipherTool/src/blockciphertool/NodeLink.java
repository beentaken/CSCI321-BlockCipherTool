/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import javafx.beans.binding.Bindings;
import javafx.fxml.FXML;

import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.layout.AnchorPane;
import javafx.scene.shape.CubicCurve;

public class NodeLink extends AnchorPane {
    
    @FXML CubicCurve node_link;
    
    public NodeLink() {
        
        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/NodeLink.fxml"));
        
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        
        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }
    
    @FXML
    private void initialize() {
        node_link.controlX1Property().bind(Bindings.add(node_link.startXProperty(), 0));
        node_link.controlX2Property().bind(Bindings.add(node_link.endXProperty(), 0));
        node_link.controlY2Property().bind(Bindings.add(node_link.startYProperty(), 0));
        node_link.controlY2Property().bind(Bindings.add(node_link.endYProperty(), 0));
    }
    
    public void setStart(Point2D startPoint) {
        
        node_link.setStartX(startPoint.getX());
        node_link.setStartY(startPoint.getY());
    }
    
    public void setEnd(Point2D endPoint) {
        
        node_link.setEndX(endPoint.getX());
        node_link.setEndY(endPoint.getY());
    }
}
