#import "GameScene.h"

// Global C++ Game Logic Object
GameLogic gameLogic;

@implementation GameScene {
    NSMutableArray<SKSpriteNode *> *ingredientSprites;
    SKLabelNode *scoreLabel;
    SKLabelNode *livesLabel;
}

- (void)didMoveToView:(SKView *)view {
    self.backgroundColor = [SKColor whiteColor];
    ingredientSprites = [NSMutableArray array];

    // Setup labels
    scoreLabel = [SKLabelNode labelNodeWithFontNamed:@"Arial"];
    scoreLabel.fontSize = 24;
    scoreLabel.fontColor = [SKColor blackColor];
    scoreLabel.position = CGPointMake(CGRectGetMidX(self.frame), self.frame.size.height - 50);
    [self addChild:scoreLabel];

    livesLabel = [SKLabelNode labelNodeWithFontNamed:@"Arial"];
    livesLabel.fontSize = 24;
    livesLabel.fontColor = [SKColor redColor];
    livesLabel.position = CGPointMake(CGRectGetMidX(self.frame), self.frame.size.height - 100);
    [self addChild:livesLabel];

    [self spawnIngredients];
}

- (void)spawnIngredients {
    // Clear existing sprites
    for (SKSpriteNode *sprite in ingredientSprites) {
        [sprite removeFromParent];
    }
    [ingredientSprites removeAllObjects];

    // Generate new ingredients
    std::vector<Ingredient>& ingredients = gameLogic.getIngredients();
    for (int i = 0; i < ingredients.size(); ++i) {
        Ingredient& ingredient = ingredients[i];

        SKSpriteNode *ingredientSprite = [SKSpriteNode spriteNodeWithImageNamed:[NSString stringWithUTF8String:ingredient.name.c_str()]];
        ingredientSprite.position = CGPointMake(arc4random_uniform(self.size.width), arc4random_uniform(self.size.height));
        ingredientSprite.name = [NSString stringWithFormat:@"%d", i]; // Use index as name
        [ingredientSprites addObject:ingredientSprite];
        [self addChild:ingredientSprite];
    }

    [self updateLabels];
}

- (void)updateLabels {
    scoreLabel.text = [NSString stringWithFormat:@"Score: %d", gameLogic.getScore()];
    livesLabel.text = [NSString stringWithFormat:@"Lives: %d", gameLogic.getLives()];
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    UITouch *touch = [touches anyObject];
    CGPoint location = [touch locationInNode:self];

    for (SKSpriteNode *sprite in ingredientSprites) {
        if (CGRectContainsPoint(sprite.frame, location)) {
            int index = sprite.name.intValue;
            gameLogic.chopIngredient(index);
            sprite.hidden = YES; // Hide sprite when chopped
            break;
        }
    }

    [self updateLabels];

    if (gameLogic.isGameOver()) {
        NSLog(@"Game Over");
    }
}

@end
