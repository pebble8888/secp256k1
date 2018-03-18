//
//  secp256k1_bitcoinTests.m
//  secp256k1_bitcoinTests
//
//  Created by pebble8888 on 2017/10/22.
//  Copyright © 2017年 pebble8888. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface secp256k1_bitcoinTests : XCTestCase

@end

@implementation secp256k1_bitcoinTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample {
    // This is an example of a functional test case.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    char* argv[] = {
        "main",
        "10",
        "0000000000000000",
    };
    
    main(3, argv);
}




@end
