


snippet_1 = '''

    run {
        my_list <- [1, 2, 3]

        my_list[. < 3].map(fn (number elem) {elem * elem})
    }
'''


snippet_2 = '''
    usertype Post {
        date post_date
        string post_content
    }

    usertype Profile {
        string name
        Post[] posts
        string? notification

        fn latest_post() {
            .posts.min(.post_date)
        }

        fn add_post(string content) {
            .posts.append(Post(now(), content))
        }
    }

    fn fetch_profile(string name) { ... }

    run {
        Profile profile <- fetch_profile('Jobe')

        if (profile.latest_post() < ago(7d)) {
            profile.notification <- 'you have not posted in a while'
        }
    }

'''