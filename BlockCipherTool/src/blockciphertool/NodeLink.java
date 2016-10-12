/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import java.lang.annotation.RetentionPolicy;
import java.util.UUID;
import javafx.beans.binding.Bindings;
import javafx.beans.binding.When;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.fxml.FXML;

import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.layout.AnchorPane;
import javafx.scene.shape.CubicCurve;

public class NodeLink extends AnchorPane {
    
    @FXML CubicCurve node_link;
    
    private final DoubleProperty mControlOffsetX = new SimpleDoubleProperty();
    private final DoubleProperty mControlOffsetY = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionX1 = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionY1 = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionX2 = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionY2 = new SimpleDoubleProperty();
    
    private String mSize;
    private String sourceId;
    private String targetId;
    
    private DragNode sourceNode;
    private DragNode targetNode;
    
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
	setId(UUID.randomUUID().toString());
    }
    
    @FXML
    private void initialize() {
        mControlOffsetX.set(100.0);
            mControlOffsetY.set(50.0);


            mControlDirectionX1.bind(new When (
                node_link.startXProperty().greaterThan(node_link.endXProperty()))
                .then(-1.0).otherwise(1.0));

            mControlDirectionX2.bind(new When (
                node_link.startXProperty().greaterThan(node_link.endXProperty()))
                .then(1.0).otherwise(-1.0));


            node_link.controlX1Property().bind(
                Bindings.add(
                    node_link.startXProperty(), mControlOffsetX.multiply(mControlDirectionX1)
                    )
                );

            node_link.controlX2Property().bind(
                Bindings.add(
                    node_link.endXProperty(), mControlOffsetX.multiply(mControlDirectionX2)
                    )
                );

            node_link.controlY1Property().bind(
                Bindings.add(
                    node_link.startYProperty(), mControlOffsetY.multiply(mControlDirectionY1)
                    )
                );

            node_link.controlY2Property().bind(
                Bindings.add(
                    node_link.endYProperty(), mControlOffsetY.multiply(mControlDirectionY2)
                    )
                );
	
    }
    
    public void setStart(Point2D startPoint) {
        
        node_link.setStartX(startPoint.getX());
        node_link.setStartY(startPoint.getY());
    }
    
    public void setEnd(Point2D endPoint) {
        
        node_link.setEndX(endPoint.getX());
        node_link.setEndY(endPoint.getY());
    }
    
    public void bindEnds (DragNode source, DragNode target) {
        node_link.startXProperty().bind(
                        Bindings.add(source.layoutXProperty(), (source.getWidth() / 2.0) - 150));
        
        node_link.startYProperty().bind(
                        Bindings.add(source.layoutYProperty(), (source.getWidth() / 2.0) - 33));

        node_link.endXProperty().bind(
                        Bindings.add(target.layoutXProperty(), (target.getWidth() / 2.0) - 150));

        node_link.endYProperty().bind(
                        Bindings.add(target.layoutYProperty(), (target.getWidth() / 2.0) - 33));
        
        source.registerLink (getId());
        target.registerLink (getId());
        
        sourceNode = source;
        targetNode = target;
        
        sourceId = source.getNodeID();
        targetId = target.getNodeID();
    }
    
    public String getLinkID() {
        return getId();
    }
    
    public void setLinkID(String myId) {
        setId(myId);
    }
    
    public String getConnectionSize() {
        return mSize;
    }
    
    public void setSize(String size) {
        mSize = size;
    }
    
    public String getSourceId() {
        return sourceId;
    }
    
    public String getTargetId() {
        return targetId;
    }
    
    public void removeLink(){
        sourceNode.removeConnection(this.getLinkID());
    }
}
