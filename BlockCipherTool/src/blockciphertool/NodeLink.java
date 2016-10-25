/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import java.lang.annotation.RetentionPolicy;
import java.util.ListIterator;
import java.util.UUID;
import javafx.beans.binding.Bindings;
import javafx.beans.binding.When;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.event.EventHandler;
import javafx.fxml.FXML;

import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.Node;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.CubicCurve;
import javafx.scene.shape.Polygon;
import javafx.scene.transform.Rotate;
//import jdk.internal.org.objectweb.asm.commons.StaticInitMerger;


/**
* @author Alex
*/
public class NodeLink extends AnchorPane {
    
    @FXML CubicCurve node_link;
    Arrow arr = null;
    
    private final DoubleProperty mControlOffsetX = new SimpleDoubleProperty();
    private final DoubleProperty mControlOffsetY = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionX1 = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionY1 = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionX2 = new SimpleDoubleProperty();
    private final DoubleProperty mControlDirectionY2 = new SimpleDoubleProperty();
    
    private MainLayout main_parent = null;
    private final NodeLink self;
    
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
	//setId(UUID.randomUUID().toString());
        
        self = this;
        
        node_link.setOnMousePressed(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if (event.isPrimaryButtonDown() && event.getClickCount() == 2) {
                    AnchorPane parent  = (AnchorPane) self.getParent();
                    parent.getChildren().remove(self);
                    main_parent.updateConnections(getId());
                }
            }
        });
    }
    
    public void addArrow() {
        /*double[] arrowShape = new double[] { 0,0,10,20,-10,20 };
        
        arr = new Arrow(node_link, 0.5f, arrowShape);
        self.getParent().
        arr.update();*/
    }
    
    public void setId(int newId) {
        setId(String.valueOf(newId));
        main_parent.updateIdCounter();
        System.out.println(getId());
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
    
    public void setParent(MainLayout main) {
        main_parent = main;
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
    //I did not write this, copied form http://stackoverflow.com/questions/26702519/javafx-line-curve-with-arrow-head
    public static class Arrow extends Polygon {

        public double rotate;
        public float t;
        CubicCurve curve;
        Rotate rz;

        public Arrow( CubicCurve curve, float t) {
            super();
            this.curve = curve;
            this.t = t;
            init();
        }

        public Arrow( CubicCurve curve, float t, double... arg0) {
            super(arg0);
            this.curve = curve;
            this.t = t;
            init();
        }

        private void init() {

            setFill(Color.web("#ff0900"));

            rz = new Rotate();
            {
                rz.setAxis(Rotate.Z_AXIS);
            }
            getTransforms().addAll(rz);

            update();
        }

        public void update() {
            double size = Math.max(curve.getBoundsInLocal().getWidth(), curve.getBoundsInLocal().getHeight());
            double scale = size / 4d;

            Point2D ori = eval(curve, t);
            Point2D tan = evalDt(curve, t).normalize().multiply(scale);

            setTranslateX(ori.getX());
            setTranslateY(ori.getY());

            double angle = Math.atan2( tan.getY(), tan.getX());

            angle = Math.toDegrees(angle);

            // arrow origin is top => apply offset
            double offset = -90;

            rz.setAngle(angle + offset);

        }

          /**
           * Evaluate the cubic curve at a parameter 0<=t<=1, returns a Point2D
           * @param c the CubicCurve 
           * @param t param between 0 and 1
           * @return a Point2D 
           */
          private Point2D eval(CubicCurve c, float t){
              Point2D p=new Point2D(Math.pow(1-t,3)*c.getStartX()+
                      3*t*Math.pow(1-t,2)*c.getControlX1()+
                      3*(1-t)*t*t*c.getControlX2()+
                      Math.pow(t, 3)*c.getEndX(),
                      Math.pow(1-t,3)*c.getStartY()+
                      3*t*Math.pow(1-t, 2)*c.getControlY1()+
                      3*(1-t)*t*t*c.getControlY2()+
                      Math.pow(t, 3)*c.getEndY());
              return p;
          }

          /**
           * Evaluate the tangent of the cubic curve at a parameter 0<=t<=1, returns a Point2D
           * @param c the CubicCurve 
           * @param t param between 0 and 1
           * @return a Point2D 
           */
          private Point2D evalDt(CubicCurve c, float t){
              Point2D p=new Point2D(-3*Math.pow(1-t,2)*c.getStartX()+
                      3*(Math.pow(1-t, 2)-2*t*(1-t))*c.getControlX1()+
                      3*((1-t)*2*t-t*t)*c.getControlX2()+
                      3*Math.pow(t, 2)*c.getEndX(),
                      -3*Math.pow(1-t,2)*c.getStartY()+
                      3*(Math.pow(1-t, 2)-2*t*(1-t))*c.getControlY1()+
                      3*((1-t)*2*t-t*t)*c.getControlY2()+
                      3*Math.pow(t, 2)*c.getEndY());
              return p;
          }
    }
}
