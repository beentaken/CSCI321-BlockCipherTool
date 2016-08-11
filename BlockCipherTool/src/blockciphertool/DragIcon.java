/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blockciphertool;

import java.io.IOException;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Point2D;
import javafx.scene.input.ClipboardContent;
import javafx.scene.input.DragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.TransferMode;
import javafx.scene.layout.AnchorPane;
/**
 *
 * @author csit321lm01a
 */
public class DragIcon extends AnchorPane{
    @FXML AnchorPane drag_icon;
    
    private EventHandler mContextDragOver;
    private EventHandler mContextDragDropped;
    
    private DragNodeType mType = null;
    
    private Point2D mDragOffset = new Point2D(0.0, 0.0);
    
    private final DragIcon self;
    
    public DragIcon() {

        FXMLLoader fxmlLoader = new FXMLLoader(
            getClass().getResource("/resources/DragIcon.fxml")
        );

        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        
        self = this;

        try {
            fxmlLoader.load();

        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }
    
    @FXML
    private void initialize() {
        buildNodeDragHandlers();
    }
    
    public void relocateToPoint (Point2D p) {
        Point2D localCoords = getParent().sceneToLocal(p);

        relocate ( 
            (int) (localCoords.getX() - mDragOffset.getX()),
            (int) (localCoords.getY() - mDragOffset.getY())
        );
    }
    
    public DragNodeType getType() { return mType;}
    
    public void setType(DragNodeType type) {

        mType = type;
        
        getStyleClass().clear();
        getStyleClass().add("dragnode");

        switch (mType) {

        case blue:
        getStyleClass().add("node-blue");
        break;

        case red:
        getStyleClass().add("node-red");            
        break;

        case green:
        getStyleClass().add("node-green");
        break;

        case grey:
        getStyleClass().add("node-grey");
        break;

        case purple:
        getStyleClass().add("node-purple");
        break;

        case yellow:
        getStyleClass().add("node-yellow");
        break;

        case black:
        getStyleClass().add("node-black");
        break;

        default:
        break;
        }
    }
    
    public void buildNodeDragHandlers() {
        
        mContextDragOver = new EventHandler <DragEvent>() {

            @Override
            public void handle(DragEvent event) {		

                event.acceptTransferModes(TransferMode.ANY);				
                relocateToPoint(new Point2D( event.getSceneX(), event.getSceneY()));

                event.consume();
            }
        };

        //dragdrop for node dragging
        mContextDragDropped = new EventHandler <DragEvent> () {

            @Override
            public void handle(DragEvent event) {

                getParent().setOnDragOver(null);
                getParent().setOnDragDropped(null);

                event.setDropCompleted(true);

                event.consume();
            }
        };
    }
    
}
