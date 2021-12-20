
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import "SceneManager.h"

@interface GLView : UIView
{
    EAGLContext  * m_context;
    SceneManager * scene;
    UILabel * textView;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesEnded:(NSSet*)touches withEvent:(UIEvent *)event;
- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
@end
